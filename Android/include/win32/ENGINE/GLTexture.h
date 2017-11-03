#pragma once
#ifdef WIN32
#include <glew.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#endif

namespace Engine {
	struct GLTexture
	{
		GLuint id;
		int width;
		int height;
	};
}