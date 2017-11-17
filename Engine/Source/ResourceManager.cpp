#include "ResourceManager.h"
namespace Engine {
	TextureCahce ResourceManager::textureCache;

	GLTexture ResourceManager::getTexture(std::string textuPath)
	{
		return textureCache.getTexture(textuPath);
	}
}