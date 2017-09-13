#pragma once
#include <string>
#include <glew.h>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();


	bool compileShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

	bool linkShaders();

private:

	bool compileShader(std::string FilePath, GLuint id);

	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

