#include "IOManager.h"
#ifndef WIN32
#include "android/asset_manager.h"
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
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
        static AAsset* file = AAssetManager_open(m_asset, filePath.c_str(), 0);
        size_t fLenght = AAsset_getLength(file);
        

	}
	bool IOManager::readFileToBuffer(std::string filePath, std::string & buffer)
	{

	}
}
#endif