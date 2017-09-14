#include "MainGame.h"
#include <Engine\Log.h>
#include <iostream>
using namespace Engine;
MainGame::MainGame(): time(0)
{

}


MainGame::~MainGame()
{
}


void MainGame::run()
{
	if (!window.init("Sphere of Influence", 1024, 640, 0))
	{
		fatal_error("Failed to init window");
	}
	else
	{	
		if(!initShaders())
		{
			goto errorend;
		}
		_sprite.push_back(new Sprite());
		_sprite.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Include/Textures/Block.png");
		_sprite.push_back(new Sprite());
		_sprite.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Include/Textures/Block.png");
		_sprite.push_back(new Sprite());
		_sprite.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Include/Textures/Block.png");
		_sprite.push_back(new Sprite());
		_sprite.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Include/Textures/Block.png");
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
	colorP.addAtribute("vertexUV");
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
		window.fpsCounter();
		static int framecounter = 0;
		if (framecounter++ == 10)
		{
			//std::cout << window.getfps() << std::endl;
			framecounter = 0;
		}
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{	
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
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
	glActiveTexture(GL_TEXTURE0);
	GLint textLoc = colorP.getUniformLoc("Textu");
	glUniform1i(textLoc, 0);

	GLint timeLoc = colorP.getUniformLoc("time");
	glUniform1f(timeLoc, time);
	for (int i = 0; i < _sprite.size(); i++)
	{
		_sprite[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	colorP.unuse();

	SDL_GL_SwapWindow(window.gWindow);
}
