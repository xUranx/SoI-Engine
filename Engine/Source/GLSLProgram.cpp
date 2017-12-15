#include "GLSLProgram.h"
#include "Log.h"
#include <fstream>
#include <vector>
#include "IOManager.h"
namespace Engine {
	GLSLProgram::GLSLProgram() : numAttribute(0), programID(0), vertexShaderID(0), fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	bool GLSLProgram::compileShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath)
	{
		Message("Creating Shaders.");

		std::string vertSource;
		std::string fragSource;

		if(!IOManager::readFileToBuffer(vertexShaderFilePath, vertSource))
		{
			fatal_error("Failed to open: " + vertexShaderFilePath);
		}
		if (!IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource))
		{
			fatal_error("Failed to open: " + fragmentShaderFilePath);
		}
		compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
		return true;
	}

	void GLSLProgram::compileShadersFromSource(const char * vertexSource, const char * fragmentSource)
	{
		programID = glCreateProgram();

		bool state = true;
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (vertexShaderID == 0)
		{
			fatal_error("Vertex shader failed to be created!");
		}
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (fragmentShaderID == 0)
		{
			fatal_error("Fragment shader failed to be created!");
		}
		Message("Compiling Shaders");
		compileShader(vertexSource, "Vertex Shader", vertexShaderID);
		compileShader(fragmentSource, "Fragment Shader", fragmentShaderID);

	}


	bool GLSLProgram::compileShader(const char* source, std::string t, GLuint id)
	{

		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint mLenght = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &mLenght);
			std::vector<char> errorLog(mLenght);
			glGetShaderInfoLog(id, mLenght, &mLenght, &errorLog[0]);

			glDeleteShader(id);
			std::string errortext = &errorLog[0];
			fatal_error("Shader " + t + " failed to compile: \n ->" + errortext);
			return false;
		}
		return true;
	}


	bool GLSLProgram::linkShaders()
	{


		//Attach our shaders to our program
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

		//Link our program
		glLinkProgram(programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

			//Don't need the program anymore.
			glDeleteProgram(programID);
			//Don't leak shaders either.
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);


			std::string iLog = &infoLog[0];
			fatal_error("Failed to link shaders: \n -> " + iLog);
			return false;
		}

		//Always detach shaders after a successful link.
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		Message("Shaders Linked");
		return true;
	}

	void GLSLProgram::addAtribute(const std::string& attName)
	{
		glBindAttribLocation(programID, numAttribute++, attName.c_str());

	}

	void GLSLProgram::use()
	{
		glUseProgram(programID);
		for (int i = 0; i < numAttribute; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);
	}

	GLint GLSLProgram::getUniformLoc(const std::string& unifromName)
	{
		GLint location = glGetUniformLocation(programID, unifromName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatal_error("Uniform " + unifromName + " doesnt exit in shader");
		}
		return location;
	}
	void GLSLProgram::dispose()
	{
		if (programID)
		{
			glDeleteProgram(programID);
		}
	}
}