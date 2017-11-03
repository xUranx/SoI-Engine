#pragma once
#ifdef WIN32


#include <SDL.h>
#include <string>

namespace Engine {
	enum WindowFlags { INVS = 0x1, FULLSCREEN = 0x2, BORDELES = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();
		//Init SDL and OpenGl
		bool init(std::string _wName, int sW, int sH, unsigned int curFlags);
		//Close SDL window
		void close();


		//The window
		SDL_Window* gWindow;

		//The surface contained by the window
		SDL_GLContext glcontext;



		//Current displayed image

		std::string Images = "Images/";
		//fps counter
		void fpsCounter();
		//Returns fps
		float getfps() { return fps; }
	private:
		std::string wName;
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		float fps, frameTime;

	};

}
#endif //WIN32