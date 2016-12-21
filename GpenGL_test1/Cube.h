// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW
#include <glfw3.h>

#include<vector>
using namespace std;

const int __cube__indices[6][6]= 
{
	{0,1,2,0,3,2},
	{4,5,6,6,7,4},
	{0,1,5,5,4,0},
	{2,3,7,7,6,2},
	{1,2,6,6,5,1},
	{0,3,7,7,4,0},
};

struct surface_len
{
	int sur_index;
	float len;
};

class cube
{


private:
	glm::vec3 _vertices[8];

public:
	cube(){}
	cube(glm::vec3  ver[])
	{
		for(int i =0; i<8; i++)
		{
			_vertices[i] = ver[i];
		}
	}
	void set_vex(glm::vec3  ver[])
	{
		for(int i =0; i<8; i++)
		{
			_vertices[i] = ver[i];
		}
	}
	float cal_incre(glm::vec3 const & move_vec, glm::mat4 const & model, char flag)
	{
		glm::vec3 dir;
		float amp_factor = 0.001;
		switch (flag)
		{
		case 'x':
			dir = glm::vec3(model[0].x, model[1].x, model[2].x);
			dir = glm::normalize(dir);
			return glm::dot(move_vec,dir)*amp_factor;
			break;
		case 'y':
			dir = glm::vec3(model[0].y, model[1].y, model[2].y);
			dir = glm::normalize(dir);
			return glm::dot(move_vec,dir)*amp_factor;
			break;
		case 'z':
			dir = glm::vec3(model[0].z, model[1].z, model[2].z);
			dir = glm::normalize(dir)*amp_factor;
			return glm::dot(move_vec,dir);
			break;
		default:
			break;
		}
	}
	void move(glm::vec3 const & move_vec, glm::mat4 const & model, int surface_index)
	{
		float increment;
		switch (surface_index)
		{
		case 0:
			increment = cal_incre(move_vec, model, 'z');
			if(_vertices[__cube__indices[0][0]].z + increment - _vertices[__cube__indices[1][0]].z < 0.001) break;
			_vertices[__cube__indices[0][0]].z += increment;
			_vertices[__cube__indices[0][1]].z += increment;
			_vertices[__cube__indices[0][2]].z += increment;
			_vertices[__cube__indices[0][4]].z += increment;
			break;
		case 1:
			increment = cal_incre(move_vec, model, 'z');
			if(_vertices[__cube__indices[0][0]].z + increment - _vertices[__cube__indices[1][0]].z < 0.001) break;
			_vertices[__cube__indices[1][0]].z += increment;
			_vertices[__cube__indices[1][1]].z += increment;
			_vertices[__cube__indices[1][2]].z += increment;
			_vertices[__cube__indices[1][4]].z += increment;
		case 2:
			increment = cal_incre(move_vec, model, 'x');
			if(_vertices[__cube__indices[2][0]].x + increment - _vertices[__cube__indices[3][0]].x < 0.001) break;
			_vertices[__cube__indices[2][0]].x += increment;
			_vertices[__cube__indices[2][1]].x += increment;
			_vertices[__cube__indices[2][2]].x += increment;
			_vertices[__cube__indices[2][4]].x += increment;
		case 3:
			increment = cal_incre(move_vec, model, 'x');
			if(_vertices[__cube__indices[2][0]].x + increment - _vertices[__cube__indices[3][0]].x < 0.001) break;
			_vertices[__cube__indices[3][0]].x += increment;
			_vertices[__cube__indices[3][1]].x += increment;
			_vertices[__cube__indices[3][2]].x += increment;
			_vertices[__cube__indices[3][4]].x += increment;
		case 4:
			increment = cal_incre(move_vec, model, 'y');
			if(_vertices[__cube__indices[4][0]].y + increment - _vertices[__cube__indices[5][0]].y < 0.001) break;
			_vertices[__cube__indices[4][0]].y += increment;
			_vertices[__cube__indices[4][1]].y += increment;
			_vertices[__cube__indices[4][2]].y += increment;
			_vertices[__cube__indices[4][4]].y += increment;
		case 5:
			increment = cal_incre(move_vec, model, 'y');
			if(_vertices[__cube__indices[4][0]].y + increment - _vertices[__cube__indices[5][0]].y < 0.001) break;
			_vertices[__cube__indices[5][0]].y += increment;
			_vertices[__cube__indices[5][1]].y += increment;
			_vertices[__cube__indices[5][2]].y += increment;
			_vertices[__cube__indices[5][4]].y += increment;
		default:
			break;
		}
	}
	void gene_gl_vertic(float *vertices, int surface_index, glm::vec3 & color)
	{
		int k = -1 ;
		for(int i = 0;i<6; i++)
		{
			vertices[++k] = _vertices[__cube__indices[surface_index][i]].x;
			vertices[++k] = _vertices[__cube__indices[surface_index][i]].y;
			vertices[++k] = _vertices[__cube__indices[surface_index][i]].z;
			vertices[++k] = color.x;
			vertices[++k] = color.y;
			vertices[++k] = color.z;
		}
	}
	bool get_intersec_triangle(glm::vec3 const & o, glm::vec3 const & dir, int vex_index[], float &t, glm::mat4 const & model)
	{
		glm::vec3 V0 = _vertices[vex_index[0]];
		glm::vec3 V1 = _vertices[vex_index[1]];
		glm::vec3 V2 = _vertices[vex_index[2]];
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

	bool get_intersec(glm::vec3 const & o, glm::vec3 const & dir, int surface_index, float & t, glm::mat4 const & model)
	{
		int vex_index[3];
		for(int i = 0; i < 3;i++)
		{
			vex_index[i] = __cube__indices[surface_index][i];
		}
		if(get_intersec_triangle(o, dir, vex_index, t, model))
		{
			return true;
		}
		
		for(int i = 3; i < 6;i++)
		{
			vex_index[i - 3] = __cube__indices[surface_index][i];
		}
		if(get_intersec_triangle(o, dir, vex_index, t, model))
		{
			return true;
		}

		return false;
	}
	bool find_insect_surface(glm::vec3 o, glm::vec3 dir, int & surface_index, glm::mat4 const & model)
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
};