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
#include "Shader.h"
//#include "Cube.h"
#include <math.h>
// Function prototypes
#include <string>
#include "objects.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLFWwindow* gl_glfw_init();

const GLuint WIDTH = 800, HEIGHT = 600;

glm::vec2 cursorpos;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

glm::vec3 cube_vertices[8] = 
{
   glm::vec3( 0.5f, -0.5f,  0.5f), 
   glm::vec3( 0.5f,  0.5f,  0.5f),
   glm::vec3(-0.5f,  0.5f,  0.5f), 
   glm::vec3(-0.5f, -0.5f,  0.5f), 
   glm::vec3( 0.5f, -0.5f, -0.5f),
   glm::vec3( 0.5f,  0.5f, -0.5f),
   glm::vec3(-0.5f,  0.5f, -0.5f),
   glm::vec3(-0.5f, -0.5f, -0.5f),
};

glm::vec3 _surface_vertex[4]=
{
	glm::vec3( 0.5f, 0.5f, 0.0f),
	glm::vec3(-0.5f, 0.5f, 0.0f),
	glm::vec3(-0.5f,-0.5f, 0.0f),
	glm::vec3( 0.5f,-0.5f, 0.0f),
};



int surface_index = -1;

axis Axis;
cube_surface Surface;

int main()
{
	GLFWwindow* window;
	window = gl_glfw_init();
   
	std::string axisshaderpath[2] = {"vertex.txt","fragment.txt"};
	std::string surfaceshader[]={ "vertex.txt", "", "fragment.txt"};
	std::string elemshader1[]={ "ins_vertex.txt", "geometry.txt", "fragment2.txt"};
	std::string elemshader2[]={ "ins_vertex.txt", "", "fragment.txt"};

	Axis.initShader(axisshaderpath);
	Axis.init();

	Surface.initShader(surfaceshader,elemshader1,elemshader2);
	Surface.init(_surface_vertex);
	 //const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
	 //printf("OOpenGL实现的版本号：%s\n",OpenGLVersion);
   	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	view =glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 

    //    GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
    //    GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
    //    GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
        // Pass them to the shaders
    //    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    //   glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    //    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		Axis.draw(model,view,projection);
		Surface.draw(model,view,projection);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}


//Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
   GLfloat incre = 0.04;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		Surface.moveedge(incre,'y','+');
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		Surface.moveedge(incre,'y','-');
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		Surface.moveedge(incre,'x','+');
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		Surface.moveedge(incre,'x','-');
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Surface.changetype(SCALE);
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Surface.changetype(CURRENT);
	}

}
//
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	static bool flag_first = true;
//	glm::vec3 cursor_pos;
//	static glm::vec3 cursor_pos_former;
//
//	if(surface_index!= -1)
//	{
//		cursor_pos.x = xpos;
//		cursor_pos.y = ypos;
//		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, WIDTH, HEIGHT);
//		glm::vec3 screenPos = glm::vec3(cursor_pos.x, HEIGHT-cursor_pos.y - 1, 0.96);
//		cursor_pos = glm::unProject(screenPos, view , projection, viewport);
//
//		if(flag_first == false)
//			Cube.move(cursor_pos,model,surface_index);
//		printf("%d\n", surface_index);
//		Cube.setbuffer();
//		cursor_pos_former = cursor_pos;
//
//		flag_first = false;
//	}
//
//	cursorpos.x = xpos;
//	cursorpos.y = ypos;
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, WIDTH, HEIGHT);
//	glm::vec3 screenPos = glm::vec3(cursorpos.x, HEIGHT-cursorpos.y - 1, 0.96);
//	glm::vec3 worldPos = glm::unProject(screenPos, view , projection, viewport);
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//	{
//		if(Cube.find_insect_surface(cameraPos,worldPos - cameraPos, surface_index, model))
//		{
//		//	printf("%d\n",surface_index);
//			Cube.changecolor(glm::vec3(1.0f, 1.0f, 1.0f),surface_index);
//			Cube.loadbuffer(surface_index);
//		}
//	}
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && surface_index != -1)
//	{
//		//printf("%d\n",surface_index);
//		Cube.changecolor(glm::vec3(1.0f, .5f, 0.2f),surface_index);
//		Cube.loadbuffer(surface_index);
//		surface_index = -1;
//	}
//}


GLFWwindow* gl_glfw_init()
{
	  // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
	
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);
    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
	
	return window;
}
