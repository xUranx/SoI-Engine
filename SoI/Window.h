#pragma once
#include <SDL.h>
#include <string>


enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

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

	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	//Current displayed image
	SDL_Surface* gCurrentSurface;
	std::string Images = "Images/";
	void gLoop();
private:

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

};

