#pragma once
#include "TextureCahce.h"
#include "GLTexture.h"
namespace Engine {
	class ResourceManager
	{
	public:
		//static GLuint boundTexture;
		static GLTexture getTexture(std::string textuPath);
	private:
		static TextureCahce textureCache;
	};
}
