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
	gl_color_ver_instance_primitive _ele_color;
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

#endif