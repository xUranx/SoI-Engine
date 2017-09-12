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
	}
	else
	{
		_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
		gLoop();
	}

	//Free resources and close SDL
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
				goto endpoint;
			}
		}
	endpoint:;
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	_sprite.draw();

	SDL_GL_SwapWindow(window.gWindow);
}
