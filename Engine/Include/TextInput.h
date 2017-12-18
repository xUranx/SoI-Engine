#pragma once
#include <string>
#ifdef WIN32
#include <SDL.h>
#endif
#include <glm\glm.hpp>
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
	class TextBox
	{
	public:
		void init(glm::vec2 dimms, glm::vec2 pos, InputMode mode);

		onEnd update();

		//#Give buffer
		void getText(std::string& buff) { buff = text; }
	private:
		glm::vec2 m_dimens;
		glm::vec2 m_pos;
		std::string& text;
		InputMode m_mode;
	};
	class TextInput
	{
	public:
		/*#Modes ALL, Numbers only, Letters only*/
		static onEnd textInput(InputMode mode, std::string& buffer);
	private:
#ifdef WIN32
		static SDL_Event ev;
#endif
	};
}

