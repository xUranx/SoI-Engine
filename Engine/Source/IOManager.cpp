#include "IOManager.h"
#include "Log.h"
#ifndef WIN32
#include <sstream>
#include <core/Log.h>
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

	AAssetManager* IOManager::m_asset;
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		int pos = filePath.find("/")+1;
        filePath.erase(filePath.begin(),filePath.begin()+pos);
        AAsset* file = AAssetManager_open(m_asset, filePath.c_str(), AASSET_MODE_BUFFER);
		if(file == nullptr)
		{
			return false;
		}
        int fLenght = AAsset_getLength(file);
		buffer.resize(fLenght);
		AAsset_read(file,(char*)&(buffer[0]), fLenght);
		AAsset_close(file);
		return true;
	}
	bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer)
	{
		int pos = filePath.find("/")+1;
		filePath.erase(filePath.begin(),filePath.begin()+pos);
		AAsset* file = AAssetManager_open(m_asset, filePath.c_str(), AASSET_MODE_BUFFER);
		if(file == nullptr)
		{
			return false;
		}
		int fLenght = AAsset_getLength(file);
		buffer.resize(fLenght);
		AAsset_read(file,(char*)&(buffer[0]), fLenght);
		AAsset_close(file);
		return true;
	}
}
#endif