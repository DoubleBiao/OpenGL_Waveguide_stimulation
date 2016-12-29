#include "objects.h"
#include <vector>

using namespace std;

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
		_ele_color.initshader((GLchar *)elemshader1[0].c_str(),(GLchar *)elemshader1[1].c_str(),(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader2[0].c_str(),(GLchar *)elemshader2[1].c_str(),(GLchar *)elemshader2[2].c_str());
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

	_ele_color.init(glm::mat4(),SCALE,0.1,0.1);
	GLfloat orign[] = {_vertex[2].x,_vertex[2].y,_vertex[2].z};
	_ele_color.react_vertexchange(orign,_vertex[0]-_vertex[1],_vertex[1] - _vertex[2],glm::vec3(_vertex[2].x,_vertex[2].y,_vertex[2].z + 1.0f) - _vertex[2]);
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

	_ele_color.react_vertexchange(orign,_vertex[0]-_vertex[1],_vertex[1] - _vertex[2],glm::vec3(_vertex[2].x,_vertex[2].y,_vertex[2].z + 1.0f) - _vertex[2]);
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

	_ele_color.react_vertexchange(orign,_vertex[0]-_vertex[1],_vertex[1] - _vertex[2],glm::vec3(_vertex[2].x,_vertex[2].y,_vertex[2].z + 1.0f) - _vertex[2]);
}



GLuint _cube_ver_indices[] = {5,4,0,3,2,6,5,1,0,4,7,3,7,6,2,1};

void cube::initShader(std::string surfaceshader[],std::string elemshader1[], std::string elemshader2[])
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
		_ele_color.initshader((GLchar *)elemshader1[0].c_str(),(GLchar *)elemshader1[1].c_str(),(GLchar *)elemshader1[2].c_str(),(GLchar *)elemshader2[0].c_str(),(GLchar *)elemshader2[1].c_str(),(GLchar *)elemshader2[2].c_str());
}

void cube::loadvertex(glm::vec3 vex[])
{
	for(int i =0; i < 8 ; i++)
	{
		_vertex[i] = vex[i];
	}
}

void cube::changetype(GLuint rendertype)
{
	_ele_color.react_changetype(rendertype);
}

void cube::init(glm::vec3 vex[])
{
	loadvertex(vex);
	_indicesnum = sizeof(_cube_ver_indices)/sizeof(GLuint); 
	GLfloat * vertextmp = new GLfloat[3 * _indicesnum];
	int k = 0;

	for(int i =0; i<_indicesnum ; i++)
	{
		vertextmp[k++]=_vertex[_cube_ver_indices[i]].x;
		vertextmp[k++]=_vertex[_cube_ver_indices[i]].y;
		vertextmp[k++]=_vertex[_cube_ver_indices[i]].z;
	}

	_surface.init(_indicesnum,vertextmp, glm::vec3(1.0f, 0.5f, 0.2f),glm::mat4());

	delete vertextmp;

	_surface.writebuffer();

	_ele_color.init(glm::mat4(),SCALE,0.5,0.5);
	GLfloat orign[] = {_vertex[7].x,_vertex[7].y,_vertex[7].z};
	_ele_color.react_vertexchange(orign,_vertex[4]-_vertex[7],_vertex[6]-_vertex[7],_vertex[3]-_vertex[7]);
}

void cube::draw(glm::mat4 const & model, glm::mat4 const & view, glm::mat4 const &projection)
{
	_surface.draw(model, view,projection);
	_ele_color.draw(model,view,projection);
}

void cube::changevertex(glm::vec3 vex[])
{
	loadvertex(vex); 
	GLfloat * vertextmp = new GLfloat[3 * _indicesnum];
	int k = 0;

	for(int i =0; i<_indicesnum ; i++)
	{
		vertextmp[k++]=_vertex[_cube_ver_indices[i]].x;
		vertextmp[k++]=_vertex[_cube_ver_indices[i]].y;
		vertextmp[k++]=_vertex[_cube_ver_indices[i]].z;
	}

	_surface.changevertex(vertextmp);

	delete vertextmp;

	GLfloat orign[] = {_vertex[7].x,_vertex[7].y,_vertex[7].z};

	_ele_color.react_vertexchange(orign,_vertex[4]-_vertex[7],_vertex[6]-_vertex[7],_vertex[3]-_vertex[7]);
}

void cube::changecolor(glm::vec3 & color)
{
	_surface.changecolor(color);
}
int _cube_ver_tris[6][6]= 
{
	{0,1,2,0,3,2},
	{4,5,6,6,7,4},
	{0,1,5,5,4,0},
	{2,3,7,7,6,2},
	{1,2,6,6,5,1},
	{0,3,7,7,4,0},
};

float cube::cal_incre(glm::vec2 const & move_vec,glm::mat4 const & model, glm::mat4 &view, glm::mat4 &projection, glm::vec4 &viewport, char flag)
{
	glm::vec3 dir;
	float amp_factor = .8e-5;
	switch (flag)
	{
	case 'x':
		dir = glm::project(glm::vec3(1.0f,0.0f,0.0f),view*model,projection,viewport);
		printf("incre: %f\n",glm::dot(move_vec,glm::vec2(dir.x,dir.y))*amp_factor);
		return glm::dot(move_vec,glm::vec2(dir.x,dir.y))*amp_factor;
		break;
	case 'y':
		dir = glm::project(glm::vec3(0.0f,1.0f,0.0f),view*model,projection,viewport);
		printf("incre: %f\n",glm::dot(move_vec,glm::vec2(dir.x,dir.y))*amp_factor);
		return glm::dot(move_vec,glm::vec2(dir.x,dir.y))*amp_factor;
		break;
	case 'z':
		dir = glm::project(glm::vec3(0.0f,0.0f,1.0f),view*model,projection,viewport);
		printf("incre: %f\n",glm::dot(move_vec,glm::vec2(dir.x,dir.y))*amp_factor);
		return glm::dot(move_vec,glm::vec2(dir.x,dir.y))*amp_factor;
		break;
	default:
		break;
	}
}

void cube::move(glm::vec2 const & move_vec, glm::mat4 const & model, glm::mat4 & view, glm::mat4 & projection, glm::vec4 & viewport,int surface_index)
{
	float increment;
	float dis_min = 0.4;
	switch (surface_index)
	{
	case 0:
		increment = cal_incre(move_vec, model,view,projection,viewport, 'z');
		if(_vertex[_cube_ver_tris[0][0]].z + increment - _vertex[_cube_ver_tris[1][0]].z < dis_min) break;
		_vertex[_cube_ver_tris[0][0]].z += increment;
		_vertex[_cube_ver_tris[0][1]].z += increment;
		_vertex[_cube_ver_tris[0][2]].z += increment;
		_vertex[_cube_ver_tris[0][4]].z += increment;
		break;
	case 1:
		increment = cal_incre(move_vec, model,view,projection,viewport, 'z');
		if(_vertex[_cube_ver_tris[0][0]].z - increment - _vertex[_cube_ver_tris[1][0]].z < dis_min) break;
		_vertex[_cube_ver_tris[1][0]].z += increment;
		_vertex[_cube_ver_tris[1][1]].z += increment;
		_vertex[_cube_ver_tris[1][2]].z += increment;
		_vertex[_cube_ver_tris[1][4]].z += increment;
		break;
	case 2:
		increment = cal_incre(move_vec, model,view,projection,viewport, 'x');
		if(_vertex[_cube_ver_tris[2][0]].x + increment - _vertex[_cube_ver_tris[3][0]].x < dis_min) break;
		_vertex[_cube_ver_tris[2][0]].x += increment;
		_vertex[_cube_ver_tris[2][1]].x += increment;
		_vertex[_cube_ver_tris[2][2]].x += increment;
		_vertex[_cube_ver_tris[2][4]].x += increment;
		break;
	case 3:
		increment = cal_incre(move_vec, model,view,projection,viewport, 'x');
		if(_vertex[_cube_ver_tris[2][0]].x - increment - _vertex[_cube_ver_tris[3][0]].x < dis_min) break;
		_vertex[_cube_ver_tris[3][0]].x += increment;
		_vertex[_cube_ver_tris[3][1]].x += increment;
		_vertex[_cube_ver_tris[3][2]].x += increment;
		_vertex[_cube_ver_tris[3][4]].x += increment;
		break;
	case 4:
		increment = cal_incre(move_vec, model,view,projection,viewport, 'y');
		if(_vertex[_cube_ver_tris[4][0]].y + increment - _vertex[_cube_ver_tris[5][0]].y < dis_min) break;
		_vertex[_cube_ver_tris[4][0]].y += increment;
		_vertex[_cube_ver_tris[4][1]].y += increment;
		_vertex[_cube_ver_tris[4][2]].y += increment;
		_vertex[_cube_ver_tris[4][4]].y += increment;
		break;
	case 5:
		increment = cal_incre(move_vec, model,view,projection,viewport, 'y');
		if(_vertex[_cube_ver_tris[4][0]].y - increment - _vertex[_cube_ver_tris[5][0]].y < dis_min) break;
		_vertex[_cube_ver_tris[5][0]].y += increment;
		_vertex[_cube_ver_tris[5][1]].y += increment;
		_vertex[_cube_ver_tris[5][2]].y += increment;
		_vertex[_cube_ver_tris[5][4]].y += increment;
		break;
	default:
		break;
	}
	changevertex(_vertex);
}

bool cube::get_intersec_triangle(glm::vec3 const & o, glm::vec3 const & dir, int vex_index[], float &t, glm::mat4 const & model)
{
	glm::vec3 V0 = _vertex[vex_index[0]];
	glm::vec3 V1 = _vertex[vex_index[1]];
	glm::vec3 V2 = _vertex[vex_index[2]];
	glm::vec4 Vtmp;

	Vtmp = model * glm::vec4(V0,1);
	V0 = glm::vec3(Vtmp.x,Vtmp.y,Vtmp.z);

	Vtmp = model * glm::vec4(V1,1);
	V1 = glm::vec3(Vtmp.x,Vtmp.y,Vtmp.z);

	Vtmp = model * glm::vec4(V2,1);
	V2 = glm::vec3(Vtmp.x,Vtmp.y,Vtmp.z);


	glm::vec3 edge1 = V1 - V0;
	glm::vec3 edge2 = V2 - V0;
	glm::vec3 pvec  = glm::cross(dir,edge2);

	float det = glm::dot(edge1,pvec);

	glm::vec3 tvec;
	if(det > 0)
	{
		tvec = o - V0;
	}
	else
	{
		det  = -det;
		tvec = V0 - o;
	}

	if(det < .0000f) return false;

	float u = glm::dot(tvec, pvec);
	if(u<0.0f || u>det) return false;

	glm::vec3 qvec = glm::cross(tvec, edge1);
	float v = glm::dot(dir, qvec);
	if(v < 0.0f || (u + v) > det) return false;

	t = glm::dot(edge2, qvec);

	float fInvDet = 1.0f / det;
	t *= fInvDet;
		
	return true;
}

bool cube::get_intersec(glm::vec3 const & o, glm::vec3 const & dir, int surface_index, float & t, glm::mat4 const & model)
{
	int vex_index[3];
	for(int i = 0; i < 3;i++)
	{
		vex_index[i] = _cube_ver_tris[surface_index][i];
	}
	if(get_intersec_triangle(o, dir, vex_index, t, model))
	{
		return true;
	}
		
	for(int i = 3; i < 6;i++)
	{
		vex_index[i - 3] = _cube_ver_tris[surface_index][i];
	}
	if(get_intersec_triangle(o, dir, vex_index, t, model))
	{
		return true;
	}

	return false;
}

bool cube::find_insect_surface(glm::vec3 o, glm::vec3 dir, int & surface_index, glm::mat4 const & model)
{
	float len;
	vector<surface_len> len_vec;
	surface_len sur_tmp;

	for(int i=0; i<6;i++)
	{
		if(get_intersec(o, dir, i, len, model))
		{
			sur_tmp.len = len;
			sur_tmp.sur_index = i;
			len_vec.push_back(sur_tmp);
		}
	}

	if(len_vec.empty()) return false;

	vector<surface_len>::iterator len_item;
	len_item = len_vec.begin();
	float tmp = len_item->len;
	surface_index = len_item->sur_index;
	len_item++;
	for(;len_item != len_vec.end(); len_item++)
	{
		if(len_item->len < tmp)
		{
			tmp = len_item->len;
			surface_index = len_item->sur_index;
		}
	}

	return true;
}