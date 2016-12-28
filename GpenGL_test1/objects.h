#ifndef OBJECTS
#define OBJECTS
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW

#include <glfw3.h>
#include "glprimitives.h"
#include <string>

class axis
{
private:
	gl_color_ver_primitive _x_axis;
	gl_color_ver_primitive _y_axis;
	gl_color_ver_primitive _z_axis;
public:
	void initShader(std::string shaderpath[]);
	void init();
	void draw(glm::mat4 const & model,glm::mat4 const & view, glm::mat4 const & projection);
};

class cube_surface
{
private:
	glm::vec3 _vertex[4];
	gl_color_ver_primitive _surface;
	gl_color_ver_instance_3d_primitive _ele_color;
public:
	cube_surface(){};
	cube_surface(glm::vec3 vertices[]);
	
	void init(glm::vec3 vex[]);
	void loadvertex(glm::vec3 vex[]);
	void initShader(std::string surfaceshader[],std::string elemshader1[], std::string elemshader2[]);
	void draw(glm::mat4 const & model, glm::mat4 const & view, glm::mat4 const &projection);
	void changevertex(glm::vec3 vex[]);
	void changetype(GLuint rendertype);

	void moveedge(GLfloat incre, char axis, char dir);
};

struct surface_len
{
	int sur_index;
	float len;
};


class cube
{
private:
	glm::vec3 _vertex[8];
	gl_color_ver_primitive _surface;
	gl_color_ver_instance_3d_primitive _ele_color;
	GLuint _indicesnum;
public:
	cube(){};
	//cube_surface(glm::vec3 vertices[]);
	
	void init(glm::vec3 vex[]);
	void loadvertex(glm::vec3 vex[]);
	void initShader(std::string surfaceshader[],std::string elemshader1[], std::string elemshader2[]);
	void draw(glm::mat4 const & model, glm::mat4 const & view, glm::mat4 const &projection);
	void changevertex(glm::vec3 vex[]);
	void changetype(GLuint rendertype);
	void changecolor(glm::vec3 & color);

	float cal_incre(glm::vec2 const & move_vec,glm::mat4 const & model, glm::mat4 &view, glm::mat4 &projection, glm::vec4 &viewport, char flag);
	void gene_gl_vertic(float *vertices, int surface_index, glm::vec3 & color);
	bool get_intersec_triangle(glm::vec3 const & o, glm::vec3 const & dir, int vex_index[], float &t, glm::mat4 const & model);
	bool get_intersec(glm::vec3 const & o, glm::vec3 const & dir, int surface_index, float & t, glm::mat4 const & model);
	bool find_insect_surface(glm::vec3 o, glm::vec3 dir, int & surface_index, glm::mat4 const & model);
	void move(glm::vec2 const & move_vec, glm::mat4 const & model, glm::mat4 & view, glm::mat4 & projection, glm::vec4 & viewport,int surface_index);
};

#endif