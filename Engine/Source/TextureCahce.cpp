#include "TextureCahce.h"
#include "ImageLoader.h"
#include "Log.h"
#define textureMap_ite std::map<std::string, GLTexture>::iterator
namespace Engine {

	TextureCahce::TextureCahce()
	{
	}


	TextureCahce::~TextureCahce()
	{
	}

	GLTexture TextureCahce::getTexture(std::string path)
	{

		textureMap_ite it = textureMap.find(path);

		if (it == textureMap.end())
		{
			//LoadTexture
			GLTexture newTexture = ImageLoader::loadPNG(path);
			textureMap.insert(make_pair(path, newTexture));
			Message("Loaded new Texture: %s\n", path.c_str());
			return newTexture;
		}
		else
		{
			//Message("Used Cahced Texture");
			return it->second;
		}

	}
}