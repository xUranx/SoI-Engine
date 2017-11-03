#pragma once
#ifdef WIN32
#include <glew.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#endif
#include "Vertex.h"
#include "GLTexture.h"
#include <string>
namespace Engine {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float _x, float _y, float _width, float _height, std::string texturePath);
		void draw();
	private:
		float x, y, width, height;
		GLuint vboID;
		GLTexture textu;

	};

}