#pragma once
#include <string>
#include <SDL.h>
namespace Engine
{
	enum InputMode
	{
		Active

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
		TextInput();
		~TextInput();
		onEnd textInput(InputMode mode, std::string& buffer);
	private:
		SDL_Event ev;
	};
}

