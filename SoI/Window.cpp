#include "Window.h"
#include <iostream>
#include <glew.h>


#ifdef _DEBUG
void fatal_error(std::string error)
{
	std::cout << error << std::endl;
}
void fatal_error(std::string error, std::string ctx)
{
	std::cout << error << ctx <<std::endl;
}
#else
void fatal_error(std::string error)
{
	
}
void fatal_error(std::string error, std::string ctx)
{
	
}
#endif


Window::Window()
{
	gWindow = NULL;
	glcontext = NULL;
}


Window::~Window()
{



}


bool Window::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SoI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (gWindow == NULL)
		{
			fatal_error("Window could not be created! SDL_Error: ", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			glcontext = SDL_GL_CreateContext(gWindow);
			GLenum test = glewInit();
			if (test != GLEW_OK)
			{
				fatal_error("Glew Init error");
				success = false;
			}
			else
			{
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			}
			
		}
	}

	return success;
}

bool Window::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	//loadSurface("C:/Users/Sami/Desktop/SDLTUT/x.bmp");


	return success;
}

void Window::close()
{

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

/*SDL_Surface* Window::loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}*/

