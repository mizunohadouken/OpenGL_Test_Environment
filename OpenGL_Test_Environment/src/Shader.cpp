#include "Shader.h"

Shader::Shader(const GLchar * vertShaderPath, const GLchar * fragShaderPath)
{
	/// 1. retrieve code from file paths ///
	std::string vertShaderCode;
	std::string fragShaderCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertShaderPath);
		fShaderFile.open(fragShaderPath);
		// read file buffer contents into stream
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertShaderCode = vShaderStream.str();
		fragShaderCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR:: Shader file not successfully read" << std::endl;

	}
	const char* vShaderCode = vertShaderCode.c_str();
	const char* fShaderCode = fragShaderCode.c_str();

	/// 2. compile shaders
	unsigned int VertShader, FragShader;

	// vertex shader compilation
	VertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertShader, 1, &vShaderCode, NULL);
	glCompileShader(VertShader);
	checkCompileErrors(VertShader, "Vertex Shader");
	// fragment shader compilation
	FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fShaderCode, NULL);
	glCompileShader(FragShader);
	checkCompileErrors(FragShader, "Fragment Shader");
	// link shaders
	ID = glCreateProgram();
	glAttachShader(ID, VertShader);
	glAttachShader(ID, FragShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "Linked Shader Program");
	// clean up
	glDeleteShader(VertShader);
	glDeleteShader(FragShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
}

void Shader::setInt(const std::string & name, int value) const
{
}

void Shader::setFloat(const std::string & name, float value) const
{
}

void Shader::checkCompileErrors(unsigned int shader, std::string shaderType)
{
	int compileResult;

	// check for compile errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (!compileResult)
	{
		int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		char* errorMessage = (char*)alloca(logLength * sizeof(char));
		glGetShaderInfoLog(shader, logLength, &logLength, errorMessage);
		std::cout << "ERROR:: " << shaderType << " compilation failed\n" << errorMessage << std::endl;
	}
}
