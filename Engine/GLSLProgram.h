#pragma once
#include <string>
#include <glew.h>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();


	bool compileShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

	void linkShaders();

private:
	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

