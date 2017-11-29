#include "TextInput.h"


#ifdef WIN32
namespace Engine {

	void TextBox::init(glm::vec2 dimms, glm::vec2 pos)
	{
		m_dimens = dimms;
		m_pos = pos;
	}
	onEnd TextInput::textInput(InputMode mode, std::string & buffer)
	{
		onEnd send = Focus;
		SDL_StartTextInput();
		if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
		{
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && buffer.length() > 0)
				buffer = buffer.substr(0, buffer.length() - 1);
			else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN)
				send = Done;
			else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)
				send = UnFocus;
			else if(ev.type == SDL_TEXTINPUT)
				buffer += ev.text.text;
		}
		SDL_StopTextInput();
		return send;
	}
}
#endif