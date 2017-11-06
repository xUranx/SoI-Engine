#pragma once
#include "Debug.h"
#if defined(WIN32) && !defined(_FES)
#include <glew.h>
#elif defined(__ANDROID__) || defined(_FES)
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