#include <GL\glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

/// constants
const unsigned int scr_width = 800;
const unsigned int scr_height = 600;

/// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

	// rendering loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
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
