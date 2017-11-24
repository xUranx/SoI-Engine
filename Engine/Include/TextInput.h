#pragma once
#include <string>
#include <SDL.h>
namespace Engine
{
	enum InputMode
	{
		All,
		Numbers,
		Letters
	};
	enum onEnd
	{
		Done,
		Focus,
		UnFocus
	};
	class TextInput
	{
	public:
		/*#Modes ALL, Numbers only, Letters only*/
		static onEnd textInput(InputMode mode, std::string& buffer);
	private:
		static SDL_Event ev;
	};
}

