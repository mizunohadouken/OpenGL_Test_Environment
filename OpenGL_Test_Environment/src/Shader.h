#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "GL\glew.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	unsigned int ID; // shader program name

	Shader(const GLchar* vertShaderPath, const GLchar* fragShaderPath);

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string shaderType);
};

#endif