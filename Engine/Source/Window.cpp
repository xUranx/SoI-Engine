#ifdef WIN32
#include "Window.h"
#include "Log.h"
#include <glew.h>
namespace Engine {

	Window::Window()
	{
		gWindow = NULL;
		glcontext = NULL;
	}


	Window::~Window()
	{



	}


	bool Window::init(std::string _wName, int sW, int sH, unsigned int curFlags)
	{
		SCREEN_WIDTH = sW;
		SCREEN_HEIGHT = sH;
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (curFlags & INVS)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (curFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (curFlags & BORDELES)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		//Initialization flag
		bool success = true;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			fatal_error("SDL could not initialize! SDL_Error: ", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			Message("SDL Initialized");
			//Create window

			gWindow = SDL_CreateWindow(_wName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sW, sH, flags);
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
					std::string versio = (char*)glGetString(GL_VERSION);
					Message("Opengl initialized. Version: " + versio);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}

			}
		}

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

	void Window::fpsCounter()
	{
		static const int NUM_SAMPLES = 100;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevticks = SDL_GetTicks();

		float currentTicks;
		currentTicks = SDL_GetTicks();

		frameTime = currentTicks - prevticks;
		frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

		prevticks = currentTicks;

		int count;

		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
		}

		float fameTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			fameTimeAverage += frameTimes[i];
		}
		fameTimeAverage /= count;
		if (fameTimeAverage > 0)
		{
			fps = 1000.0f / fameTimeAverage;
		}
		else
		{
			fps = 60.0f;
		}
		currentFrame++;
	}
}
#endif