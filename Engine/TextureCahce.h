#pragma once
#include <map>
#include "GLTexture.h"
class TextureCahce
{
public:
	TextureCahce();
	~TextureCahce();

	GLTexture getTexture(std::string path);

private:
	std::map<std::string, GLTexture> textureMap;
};

