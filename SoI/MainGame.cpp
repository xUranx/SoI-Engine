#include "MainGame.h"
#include <Engine\Log.h>



MainGame::MainGame(): time(0)
{

}


MainGame::~MainGame()
{
}


void MainGame::run()
{
	if (!window.init())
	{
		fatal_error("Failed to init window");
	}
	else
	{	
		_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
		if(!initShaders())
		{
			goto errorend;
		}
		gLoop();
	}

	//Free resources and close SDL
	errorend:
	window.close();
}

bool MainGame::initShaders()
{
	bool success = true;
	success = colorP.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	colorP.addAtribute("vertexPosition");
	colorP.addAtribute("vertexColour");
	success = colorP.linkShaders();
	return success;
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
		time += 0.01;
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{	
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		drawGame();
	}
}


void MainGame::drawGame()
{

	
	//set base depth
	glClearDepth(1.0);
	//Clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorP.use();

	GLuint timeLoc = colorP.getUniformLoc("time");
	glUniform1f(timeLoc, time);
	
	_sprite.draw();

	colorP.unuse();

	SDL_GL_SwapWindow(window.gWindow);
}
