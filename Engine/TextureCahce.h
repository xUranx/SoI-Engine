#pragma once
#include <map>
#include "GLTexture.h"
namespace Engine {
	class TextureCahce
	{
	public:
		TextureCahce();
		~TextureCahce();

		GLTexture getTexture(std::string path);

	private:
		std::map<std::string, GLTexture> textureMap;
	};
}
