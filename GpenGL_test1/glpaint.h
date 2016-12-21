#include <iostream>


#include <GL/glew.h>

// GLFW
#include <glfw3.h>

// Other Libs
#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes

class glpaint
{
private:
	GLuint VAO;
	GLuint VBO;
public:
	glpaint();
	glpaint(int buffer_num);
	~glpaint();
	void setbuffer(int buffer_num);
	void loadvertex(float * vertices, int vertice_len,GLuint vertices_state);
	void glPaintElements(GLenum mode, GLint first, GLsizei count);
};

