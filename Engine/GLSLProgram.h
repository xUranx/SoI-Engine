#pragma once
#include <string>
#include <glew.h>

namespace Engine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();


		bool compileShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

		bool linkShaders();

		void addAtribute(const std::string& attName);

		void use();
		void unuse();

		GLint getUniformLoc(const std::string& uniformName);

		void dispose();

	private:

		int numAttribute;

		bool compileShader(const char* Source, std::string t, GLuint id);

		GLuint programID;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;
	};

}