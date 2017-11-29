#pragma once
#include <string>
#include <SDL.h>
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
		void init(glm::vec2 dimms, glm::vec2 pos);
	private:
		glm::vec2 m_dimens;
		glm::vec2 m_pos;
		std::string& text;
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

