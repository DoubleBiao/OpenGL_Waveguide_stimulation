// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW

#include <glfw3.h>
#include"globject.h"
#include<vector>
using namespace std;

#ifndef CUBE
#define CUBE
struct surface_len
{
	int sur_index;
	float len;
};

class cube:public baseobject
{
public:
	cube();
	~cube(){};
	cube(glm::vec3  ver[], int vertexnum);
	cube(glm::vec3  ver[], int vertexnum, glm::vec3 color);
	void initbuffer();
	float cal_incre(glm::vec3 const & move_vec, glm::mat4 const & model, char flag);
	void move(glm::vec3 const & move_vec, glm::mat4 const & model, int surface_index);
	void gene_gl_vertic(float *vertices, int surface_index, glm::vec3 & color);
	bool get_intersec_triangle(glm::vec3 const & o, glm::vec3 const & dir, int vex_index[], float &t, glm::mat4 const & model);
	bool get_intersec(glm::vec3 const & o, glm::vec3 const & dir, int surface_index, float & t, glm::mat4 const & model);
	bool find_insect_surface(glm::vec3 o, glm::vec3 dir, int & surface_index, glm::mat4 const & model);
};
#endif