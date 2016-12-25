// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW

#include <glfw3.h>
#include"globject.h"
#include<vector>

class axis: public baseobject
{
public:
	axis();
	axis(glm::vec3 ver[], int vertexnum);
};