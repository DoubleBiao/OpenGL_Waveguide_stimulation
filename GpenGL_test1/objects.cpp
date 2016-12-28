#include "objects.h"

# define leng_fac 0.1
glm::vec3 axis_vertices[12]=
{
	glm::vec3( 2.0f,  0.0f,  0.0f),                                   // 0 :x
	glm::vec3(-1.0f,  0.0f,  0.0f),                                   // 1 :x
	glm::vec3( 0.0f,  1.0f,  0.0f),                                   // 2 :y
	glm::vec3( 0.0f, -2.0f,  0.0f),                                   // 3 :y
	glm::vec3( 0.0f,  0.0f,  1.0f),                                   // 4 :z
	glm::vec3( 0.0f,  0.0f, -2.0f),                                   // 5 :z
	glm::vec3(- sqrt(3.0)/2 * leng_fac + 2, 1/2.0 *leng_fac, 0 ),     // 6 :x
	glm::vec3(- sqrt(3.0)/2 * leng_fac + 2, -1/2.0 *leng_fac, 0 ),    // 7 :x
	glm::vec3( 1/2.0 * leng_fac, -sqrt(3.0)/2 *leng_fac + 1, 0),      // 8 :y
	glm::vec3(-1/2.0 * leng_fac, -sqrt(3.0)/2 *leng_fac + 1, 0),      // 9 :y
	glm::vec3( 1/2.0 * leng_fac, 0,-sqrt(3.0)/2 *leng_fac + 1),       // 10:z
	glm::vec3(-1/2.0 * leng_fac, 0,-sqrt(3.0)/2 *leng_fac + 1),       // 11:z
};


int __axis__indices[3][6]= 
{
	{1,0,6, 0, 7, 0},
	{3,2,8, 2, 9, 2},
	{5,4,10,4, 11,4},
};

void axis::initShader(std::string shaderpath[])
{
	_x_axis.initshader((GLchar*)shaderpath[0].c_str(),NULL,(GLchar*)shaderpath[1].c_str());
	_y_axis.initshader((GLchar*)shaderpath[0].c_str(),NULL,(GLchar*)shaderpath[1].c_str());
	_z_axis.initshader((GLchar*)shaderpath[0].c_str(),NULL,(GLchar*)shaderpath[1].c_str());
}

void axis::init()
{
	GLfloat vertextmp[6 * 3];
	int k = 0;
	for(int i = 0; i < 6; i++)
	{
		vertextmp[ k++ ] = axis_vertices[__axis__indices[0][i]].x;
		vertextmp[ k++ ] = axis_vertices[__axis__indices[0][i]].y;
		vertextmp[ k++ ] = axis_vertices[__axis__indices[0][i]].z;
	}
	_x_axis.init(6,vertextmp,glm::vec3(1.0f,0.0f,0.0f),glm::mat4());
	_x_axis.writebuffer();

	k = 0;
	for(int i = 0; i < 6 ; i++)
	{
		vertextmp[ k++ ] = axis_vertices[__axis__indices[1][i]].x;
		vertextmp[ k++ ] = axis_vertices[__axis__indices[1][i]].y;
		vertextmp[ k++ ] = axis_vertices[__axis__indices[1][i]].z;
	}
	_y_axis.init(6,vertextmp,glm::vec3(0.0f,1.0f,0.0f),glm::mat4());
	_y_axis.writebuffer();

	k = 0;
	for(int i = 0; i < 6 ; i++)
	{
		vertextmp[ k++ ] = axis_vertices[__axis__indices[2][i]].x;
		vertextmp[ k++ ] = axis_vertices[__axis__indices[2][i]].y;
		vertextmp[ k++ ] = axis_vertices[__axis__indices[2][i]].z;
	}
	_z_axis.init(6,vertextmp,glm::vec3(0.0f,0.0f,1.0f),glm::mat4());
	_z_axis.writebuffer();
}

void axis::draw(glm::mat4 const & model,glm::mat4 const & view, glm::mat4 const & projection)
{
	_x_axis.draw(model,view,projection);
	_y_axis.draw(model,view,projection);
	_z_axis.draw(model,view,projection);
}




void cube_surface::initShader(std::string surfaceshader[],std::string elemshader1[], std::string elemshader2[])
{
	if(surfaceshader[1].length()==0)
		_surface.initshader((GLchar *)surfaceshader[0].c_str(),NULL,(GLchar * )surfaceshader[2].c_str());
	else
		_surface.initshader((GLchar *)surfaceshader[0].c_str(),(GLchar * )surfaceshader[1].c_str(),(GLchar * )surfaceshader[2].c_str());
	
	if(elemshader1[1].length()==0 && elemshader2[1].length()==0)
		_ele_color.initshader((GLchar *)elemshader1[0].c_str(),NULL,(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader2[0].c_str(),NULL,(GLchar *)elemshader2[2].c_str());
	else if(elemshader1[1].length()==0)
		_ele_color.initshader((GLchar *)elemshader1[0].c_str(),NULL,(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader2[0].c_str(),(GLchar *)elemshader2[1].c_str(),(GLchar *)elemshader2[2].c_str());
	else if(elemshader2[1].length()==0)
		_ele_color.initshader((GLchar *)elemshader1[0].c_str(),(GLchar *)elemshader1[1].c_str(),(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader2[0].c_str(),NULL,(GLchar *)elemshader2[2].c_str());
	else
		_ele_color.initshader((GLchar *)elemshader1[0].c_str(),(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader2[0].c_str(),(GLchar *)elemshader2[1].c_str(),(GLchar *)elemshader2[2].c_str());
}

void cube_surface::loadvertex(glm::vec3 vex[])
{
	for(int i =0; i < 4 ; i++)
	{
		_vertex[i] = vex[i];
	}
}

void cube_surface::changetype(GLuint rendertype)
{
	_ele_color.react_changetype(rendertype);
}

void cube_surface::init(glm::vec3 vex[])
{
	loadvertex(vex);
	GLfloat vertextmp[3 * 4];
	int k = 0;

	for(int i =0; i<4 ; i++)
	{
		vertextmp[k++]=_vertex[i].x;
		vertextmp[k++]=_vertex[i].y;
		vertextmp[k++]=_vertex[i].z;
	}

	_surface.init(4,vertextmp, glm::vec3(1.0f, 0.5f, 0.2f),glm::mat4());
	_surface.writebuffer();

	_ele_color.init(glm::mat4(),SCALE);
	GLfloat orign[] = {_vertex[2].x,_vertex[2].y,_vertex[2].z};
	_ele_color.react_vertexchange(orign,_vertex[0]-_vertex[1],_vertex[1] - _vertex[2]);
}

void cube_surface::draw(glm::mat4 const & model, glm::mat4 const & view, glm::mat4 const &projection)
{
	_surface.draw(model, view,projection);
	_ele_color.draw(model,view,projection);
}

void cube_surface::changevertex(glm::vec3 vex[])
{
	loadvertex(vex);

	GLfloat vertextmp[3 * 4];
	int k = 0;
	for(int i =0; i<4 ; i++)
	{
		vertextmp[k++]=_vertex[i].x;
		vertextmp[k++]=_vertex[i].y;
		vertextmp[k++]=_vertex[i].z;
	}

	_surface.changevertex(vertextmp);
	GLfloat orign[] = {_vertex[2].x,_vertex[2].y,_vertex[2].z};

	_ele_color.react_vertexchange(orign,_vertex[0]-_vertex[1],_vertex[1] - _vertex[2]);
}

void cube_surface::moveedge(GLfloat incre, char axis, char dir)
{
	switch (axis)
	{
	case 'x':
		if(dir == '+')
		{
			_vertex[0].x += incre;
			_vertex[3].x += incre;
		}
		else
		{
			_vertex[1].x -= incre;
			_vertex[2].x -= incre;
		}
		break;
	case 'y':
		if(dir == '+')
		{
			_vertex[0].y += incre;
			_vertex[1].y += incre;
		}
		else
		{
			_vertex[2].y -= incre;
			_vertex[3].y -= incre;
		}
		break;
	default:
		break;
	}

	GLfloat vertextmp[3 * 4];
	int k = 0;
	for(int i =0; i<4 ; i++)
	{
		vertextmp[k++]=_vertex[i].x;
		vertextmp[k++]=_vertex[i].y;
		vertextmp[k++]=_vertex[i].z;
	}

	_surface.changevertex(vertextmp);
	GLfloat orign[] = {_vertex[2].x,_vertex[2].y,_vertex[2].z};

	_ele_color.react_vertexchange(orign,_vertex[0]-_vertex[1],_vertex[1] - _vertex[2]);
}