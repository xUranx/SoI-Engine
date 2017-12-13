#include "Log.h"
#include <iostream>
#include <cstdlib>
#ifndef WIN32

#include <core/Log.h>
#endif
#include <SDL.h>
namespace Engine {
#if defined(_DEBUG) && defined(WIN32)
	void fatal_error(std::string error)
	{
		std::cout << "Error: " << error << std::endl;
		SDL_Quit();
		exit(1);
	}

	void fatal_error(std::string error, std::string ctx)
	{
		std::cout << "Error: " << error << ctx << std::endl;
		SDL_Quit();
		exit(1);
	}

	void Message(std::string msg)
	{
		std::cout << "Info: " << msg << std::endl;
	}

#elif WIN32
	void fatal_error(std::string error)
	{
		std::cout << "Error: " << error << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			error.c_str(),
			NULL);
		SDL_Quit();
		exit(1);
	}
	void fatal_error(std::string error, std::string ctx)
	{
		std::cout << "Error: " << error << ctx << std::endl;
		error.append(" " + ctx);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			error.c_str(),
			NULL);
		SDL_Quit();
		exit(1);
	}
	void Message(std::string msg)
	{
		std::cout << "Info: " << msg << std::endl;
	}
#else
	extern void fatal_error(std::string error)
	{
		LOGE("Error: %s", error.c_str());
	}
	extern void fatal_error(std::string error, std::string ctx)
	{
		LOGE("Error: %s, %s", error.c_str(), ctx.c_str());
	}
	extern void Message(std::string msg)
	{
		LOGE("Info: %s", msg.c_str());
	}
#endif

}