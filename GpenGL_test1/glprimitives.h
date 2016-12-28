
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW
#include <glfw3.h>
#include<iostream>
#include<vector>
#include"shader.h"

#ifndef PRIMITIVE
#define PRIMITIVE


class glprimitive
{
protected:
	Shader _shader;
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;
public:
	virtual void initshader(const GLchar* vertexPath, const GLchar* geometrypath, const GLchar*fragmentPath)
	{
		_shader = Shader(vertexPath, geometrypath,fragmentPath);
	}
	virtual void setattributepointer() = 0;
	virtual void writeobjectanduniform() = 0;
	virtual void bindbuffers() = 0;
	virtual void unbindbuffers() = 0;
	virtual void dorendering() = 0;
	virtual void useshader() = 0;
	void draw(glm::mat4 const & model, glm::mat4 const & view, glm::mat4 const & projection)
	{
		_model = model;
		_view = view;
		_projection = projection;
		useshader();
		setattributepointer();
		writeobjectanduniform();
		bindbuffers();
		dorendering();
		unbindbuffers();
	}
};

class gl_color_ver_primitive: public glprimitive
{
protected:
	GLuint _VAO;
	GLuint _VBO;
	GLuint _verticesnum;
	GLfloat *_vertex;
	glm::vec3 _color;
	GLuint _buffer_state;
	GLuint _mode;
public:
	gl_color_ver_primitive(){_vertex = NULL;}
	~gl_color_ver_primitive()
	{
		delete _vertex;
		glDeleteBuffers(1, &_VBO);
		glDeleteVertexArrays(1, &_VAO);
	}
virtual	void writebuffer()
		{
			GLfloat *colortmp;
			colortmp = new GLfloat[_verticesnum * 3];


			int k = 0;
			for(int i = 0; i<_verticesnum; i++)
			{
				colortmp[k++] = _color.x;
				colortmp[k++] = _color.y;
				colortmp[k++] = _color.z;
			}

			glBindVertexArray(_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, _VBO);
			GLuint offset = 0;
			glBufferSubData(GL_ARRAY_BUFFER, offset, _verticesnum *3 * sizeof(GLfloat), _vertex);
			offset +=  _verticesnum *3 * sizeof(GLfloat);
			glBufferSubData(GL_ARRAY_BUFFER, offset, _verticesnum *3 * sizeof(GLfloat), colortmp);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	void init(GLuint vertexnum, GLfloat vertex[], glm::vec3 &color,
		glm::mat4 const & model,GLuint buffer_state = GL_STATIC_DRAW)
	{
		_model = model;
		_mode  = GL_LINE_LOOP;
		//yinitshader(vertexPath,fragmentPath,geometrypath);
		GLuint k = 0;
		_verticesnum = vertexnum;

		_vertex = new float[_verticesnum * 3];

		if(vertex != NULL)
		{
			for(int i = 0; i<_verticesnum; i++)
			{
				for(int j = 0; j <3 ; j++)
				{
					_vertex[k] = vertex[k++];
				}
			}
		}

		_color = color;
		_buffer_state = buffer_state;

		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
	
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _verticesnum*3*sizeof(GLfloat)*2, NULL, _buffer_state);   // vertices position and color

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(_verticesnum*3*sizeof(GLfloat)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

//		writebuffer();
	}
	void writeobjectanduniform()
	{
		GLint modelLoc = glGetUniformLocation(_shader.Program, "model");
        GLint viewLoc = glGetUniformLocation(_shader.Program, "view");
        GLint projLoc = glGetUniformLocation(_shader.Program, "projection");
        //Pass them to the shaders
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_projection));
	}
	void bindbuffers()
	{
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	}
	void unbindbuffers()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void dorendering()
	{
		glDrawArrays(_mode, 0, _verticesnum);
	}
	void setattributepointer(){}
	void changecolor(glm::vec3 const & color)
	{
		_color = color;
		bindbuffers();
		writebuffer();
		unbindbuffers();
	}
virtual	void changevertex(GLfloat * vertex)
		{
			GLuint k = 0;

			//_vertex = new float[_verticesnum * 3];

			for(int i = 0; i<_verticesnum; i++)
			{
				for(int j = 0; j <3 ; j++)
				{
					_vertex[k++] = vertex[k];
				}
			}
			bindbuffers();
			writebuffer();
			unbindbuffers();
		}
	void changemodel(glm::mat4 model)
	{
		_model = model;
	}
	void useshader()
	{
		_shader.Use();
	}
};

#define SCALE 1
#define CURRENT 2



class gl_color_ver_instance_primitive: public gl_color_ver_primitive
{
protected:
	GLuint _rownum;
	GLfloat _elem_dimen;
	GLuint _elemennum;
	glm::vec3 _rowdir;
	glm::vec3 _columndir;
	Shader _shader2;
	GLuint _rendertype;
	GLfloat *_origin;

	GLfloat _DIM_1;
	GLfloat _DIM_2;
public:
	gl_color_ver_instance_primitive(){_origin = NULL;}
	void writebuffer()
	{
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, _verticesnum *3 * sizeof(GLfloat), _vertex);
	
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	virtual void react_vertexchange(GLfloat orgine[], glm::vec3 rowdir, glm::vec3 columndir)
	{
		_rowdir = rowdir;
		_columndir = columndir;

		if(_origin != NULL)
		{
			delete _origin;
		}
		_origin = new GLfloat[3];
		for(int i =0; i<3; i++)
		{
			_origin[i] = orgine[i];
		}
		react_change();
	}

	virtual void react_changetype(GLuint rendertype)
	{
		_rendertype = rendertype;
		if(_rendertype == SCALE)
		{
			_elem_dimen = _DIM_1 ;
		}
		else
		{
			_elem_dimen = _DIM_2 ;
		}
		react_change();
	}

	virtual void react_change()
	{
		GLfloat vertex_tmp[12];
		_rownum = glm::length(_rowdir)/_elem_dimen;
		_elemennum = (glm::length(_rowdir)/_elem_dimen)*(glm::length(_columndir) /_elem_dimen);

																		   //         elementsquare:
		vertex_tmp[0 + 2 * 3] = _origin[0];                                //       1   --rowdir-->   0
		vertex_tmp[1 + 2 * 3] = _origin[1];                                //      / \               / \ 
		vertex_tmp[2 + 2 * 3] = _origin[2];								   //       |                 |
																		   //    colunmdir         columndir
		vertex_tmp[0 + 0 * 3] = _origin[0] + _columndir.x * _elem_dimen;   //       |                 |
		vertex_tmp[1 + 0 * 3] = _origin[1] + _columndir.y * _elem_dimen;   //       |                 |
		vertex_tmp[2 + 0 * 3] = _origin[2] + _columndir.z * _elem_dimen;   //       2   --rowdir-->   3 

		vertex_tmp[0 + 3 * 3] = _origin[0] + _rowdir.x * _elem_dimen;  
		vertex_tmp[1 + 3 * 3] = _origin[1] + _rowdir.y * _elem_dimen;
		vertex_tmp[2 + 3 * 3] = _origin[2] + _rowdir.z * _elem_dimen;

		vertex_tmp[0 + 1 * 3] = _origin[0] + _rowdir.x * _elem_dimen + _columndir.x * _elem_dimen;  
		vertex_tmp[1 + 1 * 3] = _origin[1] + _rowdir.y * _elem_dimen + _columndir.y * _elem_dimen;
		vertex_tmp[2 + 1 * 3] = _origin[2] + _rowdir.z * _elem_dimen + _columndir.z * _elem_dimen;

		changevertex(vertex_tmp);
	}
	void dorendering()
	{
		glDrawArraysInstancedARB(_mode, 0, _verticesnum,_elemennum);
	}
	void init(glm::mat4 const & model,GLuint rendertype,GLfloat DIM1, GLfloat DIM2, GLuint buffer_state = GL_STATIC_DRAW)
	{
		_model = model;
		_mode  = GL_LINES_ADJACENCY;
		_rendertype = rendertype;
		_DIM_1 = DIM1;
		_DIM_2 = DIM2;

		if(_rendertype == SCALE)
		{
			_elem_dimen = _DIM_1 ;
		}
		else
		{
			_elem_dimen = _DIM_2 ;
		}

		//initshader(vertexPath,fragmentPath,geometrypath);
		GLuint k = 0;
		_verticesnum = 4;

		_vertex = new float[_verticesnum * 3];

		_buffer_state = buffer_state;

		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
	
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, _verticesnum*3*sizeof(GLfloat), NULL, _buffer_state);   // vertices position and color

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void initshader(const GLchar* vertexPath1, const GLchar* geometrypath1, const GLchar*fragmentPath1,const GLchar* vertexPath2, const GLchar* geometrypath2, const GLchar*fragmentPath2)
	{
		_shader = Shader(vertexPath1,geometrypath1,fragmentPath1);
		_shader2 = Shader(vertexPath2,geometrypath2,fragmentPath2);
	}
	void writeobjectanduniform()
	{
		GLint modelLoc = glGetUniformLocation(_shader.Program, "model");
        GLint viewLoc = glGetUniformLocation(_shader.Program, "view");
        GLint projLoc = glGetUniformLocation(_shader.Program, "projection");
        // Pass them to the shaders
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_projection));

		GLint rowdirLoc = glGetUniformLocation(_shader.Program, "rowdir");
		GLint columndirLoc = glGetUniformLocation(_shader.Program, "columndir");
		GLint rownumLoc = glGetUniformLocation(_shader.Program, "rownum");
		GLint eledimensionLoc = glGetUniformLocation(_shader.Program, "eledimension");
		
		glUniform3fv(rowdirLoc, 1, glm::value_ptr(glm::normalize(_rowdir)));
		glUniform3fv(columndirLoc, 1, glm::value_ptr(glm::normalize(_columndir)));
		glUniform1i(rownumLoc, _rownum);
		glUniform1f(eledimensionLoc,_elem_dimen);
};
	void useshader()
	{
		if(_rendertype == SCALE)
		{
			_shader2.Use();
		}
		else
		{
			_shader.Use();
		}
	}
	
};


class gl_color_ver_instance_3d_primitive:public gl_color_ver_instance_primitive
{
private:
	glm::vec3 _layerdir;
	GLuint _columnnum;
public:
	void react_vertexchange(GLfloat orgine[], glm::vec3 rowdir, glm::vec3 columndir, glm::vec3 layerdir)
	{
		_layerdir = layerdir;
		gl_color_ver_instance_primitive::react_vertexchange(orgine, rowdir, columndir);
	}
	void react_change()
	{
		GLfloat vertex_tmp[12];
		_rownum = glm::length(_rowdir)/_elem_dimen;
		_columnnum = glm::length(_columndir)/_elem_dimen;
		_elemennum = (glm::length(_rowdir)/_elem_dimen)*(glm::length(_columndir) /_elem_dimen)*(glm::length(_layerdir)/_elem_dimen);

																		   //         elementsquare:
		vertex_tmp[0 + 2 * 3] = _origin[0];                                //       1   --rowdir-->   0
		vertex_tmp[1 + 2 * 3] = _origin[1];                                //      / \               / \ 
		vertex_tmp[2 + 2 * 3] = _origin[2];								   //       |                 |
																		   //    colunmdir         columndir
		vertex_tmp[0 + 0 * 3] = _origin[0] + _columndir.x * _elem_dimen;   //       |                 |
		vertex_tmp[1 + 0 * 3] = _origin[1] + _columndir.y * _elem_dimen;   //       |                 |
		vertex_tmp[2 + 0 * 3] = _origin[2] + _columndir.z * _elem_dimen;   //       2   --rowdir-->   3 

		vertex_tmp[0 + 3 * 3] = _origin[0] + _rowdir.x * _elem_dimen;  
		vertex_tmp[1 + 3 * 3] = _origin[1] + _rowdir.y * _elem_dimen;
		vertex_tmp[2 + 3 * 3] = _origin[2] + _rowdir.z * _elem_dimen;

		vertex_tmp[0 + 1 * 3] = _origin[0] + _rowdir.x * _elem_dimen + _columndir.x * _elem_dimen;  
		vertex_tmp[1 + 1 * 3] = _origin[1] + _rowdir.y * _elem_dimen + _columndir.y * _elem_dimen;
		vertex_tmp[2 + 1 * 3] = _origin[2] + _rowdir.z * _elem_dimen + _columndir.z * _elem_dimen;

		changevertex(vertex_tmp);
	}
	void writeobjectanduniform()
	{
		GLint modelLoc = glGetUniformLocation(_shader.Program, "model");
        GLint viewLoc = glGetUniformLocation(_shader.Program, "view");
        GLint projLoc = glGetUniformLocation(_shader.Program, "projection");
        // Pass them to the shaders
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_projection));

		GLint rowdirLoc = glGetUniformLocation(_shader.Program, "rowdir");
		GLint columndirLoc = glGetUniformLocation(_shader.Program, "columndir");
		GLint layerdirLoc = glGetUniformLocation(_shader.Program, "layerdir");
		GLint rownumLoc = glGetUniformLocation(_shader.Program, "rownum");
		GLint columnnumLoc = glGetUniformLocation(_shader.Program, "columnnum");
		GLint eledimensionLoc = glGetUniformLocation(_shader.Program, "eledimension");
		
		glUniform3fv(rowdirLoc, 1, glm::value_ptr(glm::normalize(_rowdir)));
		glUniform3fv(columndirLoc, 1, glm::value_ptr(glm::normalize(_columndir)));
		glUniform3fv(layerdirLoc, 1, glm::value_ptr(glm::normalize(_layerdir)));
		glUniform1i(rownumLoc, _rownum);
		glUniform1i(columnnumLoc, _columnnum);
		glUniform1f(eledimensionLoc,_elem_dimen);
	}
};
#endif
