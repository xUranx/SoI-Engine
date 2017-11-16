#include "IOManager.h"
#ifndef WIN32
#include "android/asset_manager.h"
#include "android/obb.h"
#endif
#ifdef WIN32
#include <fstream>
namespace Engine {
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			return false;
		}
		file.seekg(0, std::ios::end);

		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read((char *)&(buffer[0]), fileSize);
		file.close();
		return true;
	}
	bool IOManager::readFileToBuffer(std::string filePath, std::string & buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			return false;
		}
		file.seekg(0, std::ios::end);

		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read((char *)&(buffer[0]), fileSize);
		file.close();
		return true;
	}
}
#else

namespace Engine {
	AAssetManager* IOManager::m_asset;
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		int pos = filePath.find("/");
		filePath.erase(0,pos+1);
        static AAsset* file = AAssetManager_open(m_asset, filePath.c_str(), 0);
        int fLenght = AAsset_getLength(file);
		int nb_read = 0;
		buffer.resize(fLenght);
		AAsset_read(file,(char*)&buffer[0], BUFSIZ);

	}
	bool IOManager::readFileToBuffer(std::string filePath, std::string & buffer)
	{

	}
}
#endif