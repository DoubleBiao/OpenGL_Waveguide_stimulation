
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW
#include <glfw3.h>
#include<iostream>
#include<vector>

#ifndef GLOBJECT
#define GLOBJECT
#include"glpaint.h"

using namespace std;

//const int __cube__indices[6][6]= 
//{
//	{0,1,2,0,3,2},
//	{4,5,6,6,7,4},
//	{0,1,5,5,4,0},
//	{2,3,7,7,6,2},
//	{1,2,6,6,5,1},
//	{0,3,7,7,4,0},
//};

//struct surface_len
//{
//	int sur_index;
//	float len;
//};

class globject_part
{
public:
	int _indices_num;
	int * _vex_indices;
	glm::vec3 _color;

	globject_part()
	{
		_indices_num = 0;
		_vex_indices = NULL;
	}
	~globject_part()
	{
		delete(_vex_indices);
	}
	globject_part & operator=(const globject_part & leftopprand)
	{
		_indices_num = leftopprand._indices_num;
		_color = leftopprand._color;

		delete _vex_indices;
		_vex_indices = new int[_indices_num];
		for(int i = 0; i<_indices_num; i++)
		{
			_vex_indices[i] = leftopprand._vex_indices[i];
		}
		return *this;
	}
	void assign_index(int indices[], int indicesnum)
	{
		_indices_num = indicesnum;
		delete _vex_indices;
		_vex_indices = new int[_indices_num];
		for(int i = 0; i<_indices_num; i++)
		{
			_vex_indices[i] = indices[i];
		}
	}
};

class baseobject
{
//protected:
public:
	glpaint *_paintobject;
	int _vextexnum;
	int _partnum;
	glm::vec3 * _vertices;
	globject_part * _part;
public:
	baseobject(){_vertices = NULL; _part = NULL;_paintobject = NULL;};
	baseobject(glm::vec3  ver[], int vertexnum,globject_part part[], int partnum)
	{
		_paintobject = new glpaint[partnum];
		
		for(int i =0; i< partnum;i++)
		{
			_paintobject[i].setbuffer(1);
		}

		_vextexnum = vertexnum;
		_partnum = partnum;
		_vertices = new glm::vec3[vertexnum];
		_part = new globject_part[partnum];
		for(int i = 0; i < vertexnum; i++)
		{
			_vertices[i] = ver[i];
		}
		for(int i = 0 ;i < partnum; i++)
		{
			_part[i] = part[i];
		}
	}

	void init_buffer(int partnum)
	{
		_paintobject = new glpaint[partnum];
	
		for(int i =0; i< partnum;i++)
		{
			_paintobject[i].setbuffer(1);
		}
	}
	void init_buffer()
	{
		_paintobject = new glpaint[_partnum];
	
		for(int i =0; i< _partnum;i++)
		{
			_paintobject[i].setbuffer(1);
		}
	}
	void set_vex(glm::vec3  ver[], int vertexnum)
	{
		delete _vertices;
		_vextexnum = vertexnum;
		_vertices = new glm::vec3[vertexnum];
		for(int i = 0;i<vertexnum;i++)
		{
			_vertices[i] = ver[i];
		}
	}
	void set_part(globject_part part[], int partnum)
	{
		delete _part;
		_partnum = partnum;
		
		_part = new globject_part[partnum];

		for(int i = 0; i<partnum; i++)
		{
			_part[i] = part[i];
		}
	}
	void set_color(glm::vec3 color[], int colornum)
	{
		for(int i = 0; i<colornum; i++)
		{
			_part->_color = color[i];
		}
	}
	void changecolor(glm::vec3 const & color, int partindex)
	{
		_part[partindex]._color = color;
	}
	void set_indices(int ** indices,int indices_len[], int partnum)
	{
		for(int i = 0; i<partnum; i++)
		{
			_part[i].assign_index(*(indices+i),indices_len[i]);
		}
	}

	void loadbuffer(int partid, GLuint vertices_state = GL_STATIC_DRAW)
	{
		int verticesnum = _part[partid]._indices_num;
		int k = -1 ;
		float * vertices = new float[verticesnum * 6];

		for(int i = 0;i<verticesnum; i++)
		{
			vertices[++k] = _vertices[_part[partid]._vex_indices[i]].x;
			vertices[++k] = _vertices[_part[partid]._vex_indices[i]].y;
			vertices[++k] = _vertices[_part[partid]._vex_indices[i]].z;
			vertices[++k] = _part[partid]._color.x;
			vertices[++k] = _part[partid]._color.y;
			vertices[++k] = _part[partid]._color.z;
		}
		_paintobject[partid].loadvertex(vertices, verticesnum * 6 * sizeof(float),vertices_state);
	}
	void setbuffer(GLuint vertices_state = GL_STATIC_DRAW)
	{
		for(int i=0; i<_partnum; i++)
		{
			loadbuffer(i, vertices_state);
		}
	}

	void drawobject_part(int partid, GLenum mode = GL_TRIANGLES)
	{
		_paintobject[partid].glPaintElements(mode, 0, _part[partid]._indices_num);
	}
	void draw(GLenum mode = GL_TRIANGLES)
	{
		for(int i = 0;i<_partnum;i++)
		{
			_paintobject[i].glPaintElements(mode, 0, _part[i]._indices_num);
		}
	}
};
#endif