#include "Window.h"
#include <glew.h>
#include "Log.h"




Window::Window(std::string _wName): wName(_wName)
{
	gWindow = NULL;
	glcontext = NULL;
	SCREEN_WIDTH = 1024;
	SCREEN_HEIGHT = 720;
}


Window::~Window()
{



}


bool Window::init()
{
	
	//Initialization flag
	bool success = true;
	Message("SDL Initialized");
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fatal_error("SDL could not initialize! SDL_Error: ", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		
		gWindow = SDL_CreateWindow(wName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (gWindow == NULL)
		{
			fatal_error("Window could not be created! SDL_Error: ", SDL_GetError());
			success = false;
		}
		else
		{	
			Message("Window initialized");
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
				Message("Opengl initialized");
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
	Message("Closing");
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

