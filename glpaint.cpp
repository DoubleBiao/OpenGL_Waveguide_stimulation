#include"glpaint.h"
#include "Shader.h"

glpaint::~glpaint()
{
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
glpaint::glpaint(){}

glpaint::glpaint(int buffer_num)
{
	glGenVertexArrays(buffer_num, &VAO);
    glGenBuffers(buffer_num, &VBO);
}

void glpaint::setbuffer(int buffer_num)
{

	glGenVertexArrays(buffer_num, &VAO);
    glGenBuffers(buffer_num, &VBO);
}

void glpaint::loadvertex(float * vertices, int vertice_len,GLuint vertices_state)
{
	glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertice_len, vertices, vertices_state);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO
}

void glpaint::glPaintElements(GLenum mode, GLint first, GLsizei count)
{
	glBindVertexArray(VAO);
	//glDrawArrays(GL_LINES, 0, 36);
	glDrawArrays(mode, first, count);
	glBindVertexArray(0);
}