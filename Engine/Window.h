#pragma once
#include <SDL.h>
#include <string>

enum WindowFlags{INVS = 0x1, FULLSCREEN = 0x2, BORDELES = 0x4};

class Window
{
public:
	Window();
	~Window();
	bool init(std::string _wName, int sW, int sH, unsigned int curFlags);
	bool loadMedia();
	void close();
	
	//SDL_Surface* loadSurface(std::string path);

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The surface contained by the window
	SDL_GLContext glcontext;



	//Current displayed image

	std::string Images = "Images/";
	void fpsCounter();
	float getfps() { return fps; }
private:
	std::string wName;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	float fps, frameTime;

};

