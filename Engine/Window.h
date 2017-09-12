#pragma once
#include <SDL.h>
#include <string>



class Window
{
public:
	Window();
	~Window();
	bool init();
	bool loadMedia();
	void close();
	
	//SDL_Surface* loadSurface(std::string path);

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The surface contained by the window
	SDL_GLContext glcontext;



	//Current displayed image

	std::string Images = "Images/";
private:

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

};

