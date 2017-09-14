#include "ResourceManager.h"

TextureCahce ResourceManager::textureCache;

GLTexture ResourceManager::getTexture(std::string textuPath)
{
	return textureCache.getTexture(textuPath);
}
