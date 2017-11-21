#include "TextInput.h"

namespace Engine
{
	TextInput::TextInput()
	{
	}


	TextInput::~TextInput()
	{
	}
#ifdef WIN32
	onEnd TextInput::textInput(InputMode mode, std::string & buffer)
	{
		onEnd send = Focus;
		SDL_StartTextInput();
		if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
		{
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && buffer.length() > 0)
				buffer = buffer.substr(0, buffer.length() - 1);
			else if(ev.type == SDL_TEXTINPUT)
				buffer += ev.text.text;
		}
		else if (mode == Active && ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym = SDLK_RETURN)
				send = Done;
		}
		SDL_StopTextInput();
		return send;
	}
}
#endif