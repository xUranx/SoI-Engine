#include "Window.h"
#include "Equations.h"
#include <iostream>
#include <glew.h>

using namespace std;



int main(int argc, char* args[])
{
	Window window;
	if (!window.init())
	{
		#if _DEBUG
			printf("Failed to initialize!\n");
		#endif
	}
	else
	{
		//Load media
		if (!window.loadMedia())
		{
			#if _DEBUG
				printf("Failed to load media!\n");
			#endif
		}
		else
		{
			window.gLoop();
			
		}
	}

	//Free resources and close SDL
	errorexit:
	window.close();
	return 0;
	//printf("SoI = %f\n", SoI(2000.0,400.0, 5000.0));
}