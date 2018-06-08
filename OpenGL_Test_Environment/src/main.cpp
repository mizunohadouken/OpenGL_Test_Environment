#include <GL\glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "Shader.h"

#define USE_WIRE_FRAME 0

/// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

/// settings
const unsigned int scr_width = 800;
const unsigned int scr_height = 600;

int main()
{
	// initialize glfw
	glfwInit();
	if (!glfwInit())
	{
		std::cout << "Failed to create initialize glfw" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window and make current context
	GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "OpenGL Test Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error! Failed to initialize GLEW" << std::endl;
	}

	/// build and compile shaders
	Shader shaderClass("res/shaders/vertexshader.vert", "res/shaders/fragmentshader.frag");


	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	unsigned int indices[] = {
		0 , 1, 3, // triangle 1
		1 , 2, 3
	};

	// setup vao, vbo, ebo
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind vertex array to prevent changes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

#if USE_WIRE_FRAME
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

	// rendering loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		// render here
		glClearColor(.2f, .2f, .2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderClass.use();
		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// end rendering
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// call whenever window size changes
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
