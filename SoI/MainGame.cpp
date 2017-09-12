#include "MainGame.h"



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}


void MainGame::run()
{
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
			gLoop();
		}
	}

	//Free resources and close SDL
	errorexit:
	window.close();
}

void MainGame::gLoop()
{

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running

	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

	}
}