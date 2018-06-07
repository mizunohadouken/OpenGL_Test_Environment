#include <GL\glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

#define USE_EBO 0
#define USE_WIRE_FRAME 0
#define EXERCISE_1 0
#define EXERCISE_2 1
#define USE2SHADERS 1

/// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


/// settings
const unsigned int scr_width = 800;
const unsigned int scr_height = 600;

/// shaders
const char *vertexShaderSrc = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragShaderSrc = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char *fragShaderSrc2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

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
	unsigned int VertexShader, FragShader, ShaderProgram;
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(VertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
		std::cout << "ERROR:: VertexShader compilation failed\n" << infoLog << std::endl;
	}

	FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(FragShader);
	glGetShaderiv(FragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragShader, 512, NULL, infoLog);
		std::cout << "ERROR:: FragShader compilation failed\n" << infoLog << std::endl;
	}

	// link shaders
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragShader);
	glLinkProgram(ShaderProgram);
	glGetShaderiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR:: Shader linking failed\n" << infoLog << std::endl;
	}


#if USE2SHADERS
	unsigned int FragShader2, ShaderProgram2;

	FragShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader2, 1, &fragShaderSrc2, NULL);
	glCompileShader(FragShader2);
	glGetShaderiv(FragShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragShader2, 512, NULL, infoLog);
		std::cout << "ERROR:: FragShade2 compilation failed\n" << infoLog << std::endl;
	}

	ShaderProgram2 = glCreateProgram();
	glAttachShader(ShaderProgram2, VertexShader);
	glAttachShader(ShaderProgram2, FragShader2);
	glLinkProgram(ShaderProgram2);
	glGetShaderiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderProgram2, 512, NULL, infoLog);
		std::cout << "ERROR:: Shader linking failed\n" << infoLog << std :: endl;
	}

	glDeleteShader(FragShader2);
#endif

	// clean up shaders
	glDeleteShader(VertexShader);
	glDeleteShader(FragShader);

#if EXERCISE_1
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-0.6f, 0.0f, 0.0f
	};
#elif EXERCISE_2
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	float vertices2[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-0.6f, 0.0f, 0.0f
	};
	
#else
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
#endif

	float sqVertices[] = {
		-.5f,  .5f, 0.0f, // top left
		 .5f,  .5f, 0.0f, // top right
		 .5f, -.5f, 0.0f, // bottom right
		-.5f, -.5f, 0.0f // bottom left
	};

	unsigned int indices[] = {
		0 , 1, 2, // triangle 1
		3, 2, 0 // triangle 2
	};


	// setup vao, vbo, ebo
	unsigned int vao, vao2, vbo, vbo2, ebo;
	glGenVertexArrays(1, &vao);
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ebo);


	glBindVertexArray(vao);

#if USE_EBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sqVertices), sqVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#else
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#endif

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind vertex array to prevent changes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

#if EXERCISE_2
	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

#endif

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

		glUseProgram(ShaderProgram);
		glBindVertexArray(vao);

#if USE_EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#else
#if EXERCISE_1
		glDrawArrays(GL_TRIANGLES, 0, 6);
#elif EXERCISE_2
		glDrawArrays(GL_TRIANGLES, 0, 3);
#if USE2SHADERS
		glUseProgram(ShaderProgram2);
#endif

		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
#else
		glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
#endif	

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
