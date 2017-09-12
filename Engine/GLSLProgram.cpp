#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : programID(0), vertexShaderID(0), fragmentShaderID(0)
{

}


GLSLProgram::~GLSLProgram()
{
}

bool GLSLProgram::compileShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath)
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
	{
		fatal_error("Vertex shader failed to be created!");
		return false;
	}
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0)
	{
		fatal_error("Fragment shader failed to be created!");
		return false;
	}
	std::ifstream vertexFile(vertexShaderFilePath);
	if (vertexFile.fail())
	{
		fatal_error("Failed to open: " + vertexShaderFilePath);
	}

	std::string fileContents;
	std::string Line;

	while (std::getline(vertexFile, Line))
	{
		fileContents += Line + "\n";
	}
	vertexFile.close();

	const char* contetnsPtr = fileContents.c_str();
	glShaderSource(vertexShaderID, 1, &contetnsPtr, nullptr);
	glCompileShader(vertexShaderID);

	GLint success = 0;
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &success);
	if (success == GL_FALSE)
	{
		GLint mLenght = 0;
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &mLenght);
		std::vector<char> errorLog(mLenght);
		glGetShaderInfoLog(vertexShaderID, mLenght, &mLenght, &errorLog[0]);

		glDeleteShader(vertexShaderID);
		std::string errortext = &errorLog[0];
		fatal_error("Vertex shader failed to compile: \n" + errortext);
	}

}

void GLSLProgram::linkShaders()
{

}


