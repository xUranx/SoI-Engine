#pragma once
#include <vector>
#include <string>
#ifndef WIN32
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#endif
namespace Engine {
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(std::string filePath, std::string& buffer);
#ifndef WIN32
        static AAssetManager* m_asset;
#endif // !WIN32
	};
}

