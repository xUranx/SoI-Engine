#include "InputManager.h"
#define keyMapIt std::unordered_map<unsigned int, bool>::iterator

namespace Engine
{

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		keyMap[keyID] = true;
	}
	void InputManager::releaseKey(unsigned int keyID)
	{
		keyMap[keyID] = false;
	}
	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		keyMapIt it = keyMap.find(keyID);
		if (it != keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}
}