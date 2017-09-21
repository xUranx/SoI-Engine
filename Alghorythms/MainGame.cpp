#include "MainGame.h"
#include <Engine\Log.h>
#include <Engine\ResourceManager.h>
#include <random>
#include <algorithm>
#include <math.h>
#include <iostream>
using namespace Engine;

MainGame::MainGame()
{
	sWidth = 640;
	sHeight = 320;
}


MainGame::~MainGame()
{
}


void MainGame::run()
{
	if (!window.init("DataStructures", sWidth, sHeight, 0))
	{
		fatal_error("Failed to Init");
	}
	else
	{
		//Load media
		if (!initShaders())
		{
			fatal_error("Failed to init shaders");
		}
		else
		{
			spriteBatch.init();
			gLoop();
		}
	}

	//Free resources and close SDL
	window.close();
}

bool MainGame::initShaders()
{
	bool success = true;
	success = colorP.compileShaders("../SoI/Shaders/colorShading.vert", "../SoI/Shaders/colorShading.frag");
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
	cam2D.init(sWidth,sHeight);
	cam2D.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
	//Event handler
	SDL_Event e;

	//While application is running
	bool sorted = false;
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
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				default:
					break;
				}
			}
		}
		cam2D.update();
		
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

	//GLint timeLoc = colorP.getUniformLoc("time");
	//glUniform1f(timeLoc, time);

	GLint pLoc = colorP.getUniformLoc("P");
	glm::mat4 camMatrix = cam2D.getCameraMatrix();
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &(camMatrix[0][0]));

	

	spriteBatch.end();
	spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	colorP.unuse();

	SDL_GL_SwapWindow(window.gWindow);
}

bool MainGame::compFrontToBack(glm::vec4* a, glm::vec4* b)
{ 
	return (a->w < b->w); 
}