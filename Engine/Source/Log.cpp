#include "Log.h"
#include <iostream>
#include <cstdlib>
#include <SDL.h>
namespace Engine {
#if defined(_DEBUG) && defined(WIN32)
	extern void fatal_error(std::string error)
	{
		std::cout << "Error: " << error << std::endl;
		SDL_Quit();
		exit(1);
	}

	extern void fatal_error(std::string error, std::string ctx)
	{
		std::cout << "Error: " << error << ctx << std::endl;
		SDL_Quit();
		exit(1);
	}

	extern void Message(std::string msg)
	{
		std::cout << "Info: " << msg << std::endl;
	}

#elif WIN32
	extern void fatal_error(std::string error)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			error.c_str(),
			NULL);
		SDL_Quit();
		exit(1);
	}
	extern void fatal_error(std::string error, std::string ctx)
	{
		error.append(" " + ctx);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error",
			error.c_str(),
			NULL);
		SDL_Quit();
		exit(1);
	}
	extern void Message(std::string msg)
	{

	}
#else
	extern void fatal_error(std::string error)
	{
	
	}
	extern void fatal_error(std::string error, std::string ctx)
	{
	
	}
	extern void Message(std::string msg)
	{

	}
#endif

}