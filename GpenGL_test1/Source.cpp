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
#include "Cube.h"
#include "glpaint.h"
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLFWwindow* gl_glfw_init();

const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop

glm::vec2 cursorpos;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

glm::vec3 vertices[8] = 
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

cube Cube;
glpaint surface_array[6];
int surface_index = -1;

int main()
{
	GLFWwindow* window;
	window = gl_glfw_init();
    // Build and compile our shader program
    Shader ourShader("vertex.txt", "fragment.txt");
	Cube.set_vex(vertices);
    // Set up vertex data (and buffer(s)) and attribute pointers
	float vertex_temp[6 * 6];

	
	for(int i=0; i<6; i++)
	{
		surface_array[i].setbuffer(1);
		Cube.gene_gl_vertic(vertex_temp,i,glm::vec3(1.0f, 0.5f, 0.2f));
		surface_array[i].loadvertex(vertex_temp,sizeof(vertex_temp),GL_DYNAMIC_DRAW);
	}

	//loadbuffer(VAO, VBO, vertices, sizeof(vertices));
	//loadbuffer(VAO1, VBO1, vertices1, sizeof(vertices1));

	
    
   	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	view =glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Activate shader
        ourShader.Use();

        // Create transformations
       
        // Get their uniform location
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
        // Pass them to the shaders
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		for(int i=0; i<6; i++)
		{
			surface_array[i].glPaintElements(GL_TRIANGLES, 0,6);
		}

		//glBindVertexArray(VAO1);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
  
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}


// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

}

void loadbuffer(GLuint VAO, GLuint VBO, GLuint EBO, GLfloat vertices[], int vertice_len, GLuint indices[], GLuint indices_len, GLuint vertices_state)
{
	glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertice_len, vertices, vertices_state);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_len, indices, GL_STATIC_DRAW); 

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO
}

glm::vec3 cal_normal(glm::vec3 a1, glm::vec3 a2, glm::vec3 a_ref, glm::vec3 o)
{
	glm::vec3 oa1 = a1 - o;
	glm::vec3 oa2 = a2 - o;

	glm::vec3 oa_ref = a_ref - o;

	glm::vec3 n = glm::cross(oa1, oa2);

	if(glm::dot(n,a_ref) > 0)
	{
		n = -n;
	}
	return n;
}

bool intersect(glm::vec3 vex[], glm::vec3 a, glm::vec3 o)
{
	glm::vec3 n[4];
	for(int i = 0; i<4;i++)
	{
		n[i] = cal_normal(vex[(0+i)%4],vex[(1+i)%4],vex[(2+i)%4],o);
	}
	
	glm::vec3 ray = a - o;

	float in_pr[4];
	for(int i = 0 ; i<4;i++)
	{
		in_pr[i] = glm::dot(n[i], ray);
	}

	for(int i = 1; i<4 ;i++)
	{
		if(in_pr[0]*in_pr[i]<0)
		{
			return false;
		}
	}

	return true ;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec3 cursor_move;

	if(surface_index!= -1)
	{
		float vertex_temp[6 * 6];
		cursor_move.x = xpos - cursorpos.x;
		cursor_move.y = ypos - cursorpos.y;
		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, WIDTH, HEIGHT);
		glm::vec3 screenPos = glm::vec3(cursor_move.x, HEIGHT-cursor_move.y - 1, 0.96);
		cursor_move = glm::unProject(screenPos, view , projection, viewport);
		Cube.move(cursor_move,model,surface_index);

		for(int i=0; i<6; i++)
		{
			surface_array[i].setbuffer(1);
			Cube.gene_gl_vertic(vertex_temp,i,glm::vec3(1.0f, 0.5f, 0.2f));
			surface_array[i].loadvertex(vertex_temp,sizeof(vertex_temp),GL_DYNAMIC_DRAW);
		}
	}

	cursorpos.x = xpos;
	cursorpos.y = ypos;


}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	float vertex_temp[6 * 6];
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, WIDTH, HEIGHT);
	glm::vec3 screenPos = glm::vec3(cursorpos.x, HEIGHT-cursorpos.y - 1, 0.96);
	glm::vec3 worldPos = glm::unProject(screenPos, view , projection, viewport);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if(Cube.find_insect_surface(cameraPos,worldPos - cameraPos, surface_index, model))
		{
			printf("%d\n",surface_index);
			Cube.gene_gl_vertic(vertex_temp,surface_index,glm::vec3(1.0f, 1.0f, 1.0f));
			surface_array[surface_index].loadvertex(vertex_temp,sizeof(vertex_temp),GL_DYNAMIC_DRAW);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && surface_index != -1)
	{
		printf("%d\n",surface_index);
		Cube.gene_gl_vertic(vertex_temp,surface_index,glm::vec3(1.0f, 0.5f, 0.2f));
		surface_array[surface_index].loadvertex(vertex_temp,sizeof(vertex_temp),GL_DYNAMIC_DRAW);
		surface_index = -1;
	}
}


GLFWwindow* gl_glfw_init()
{
	  // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
	
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
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