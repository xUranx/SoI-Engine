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

	void addAtribute(const std:: string& attName);

	void use();
	void unuse();

private:

	int numAttribute;

	bool compileShader(std::string FilePath, GLuint id);

	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

