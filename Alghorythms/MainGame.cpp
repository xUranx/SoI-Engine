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
	sWidth = 1024;
	sHeight = 640;
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
			UIspriteBatch.init();
			spriteFont = new SpriteFont("../SoI/Include/Fonts/font.ttf", 16);
			b2Vec2 grav(0.0f, -9.81);
			glm::vec2 dimes = glm::vec2(50.0f, 3.0f);
			world = std::make_unique<b2World>(grav);
			Ground.Fixedinit(world.get(), glm::vec2(0.0f, -15.0f), dimes);
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
	hudCam.init(sWidth, sHeight);
	//cam2D.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
	hudCam.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
	//cam2D.setScale(18.0f);
	//Event handler
	SDL_Event e;
	map.init("Level1", 20, 100);
	const float CamSpeed = 0.5f;
	const float ScalSpeed = 0.5f;
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
				case SDLK_w:
					cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, -CamSpeed));
					break;
				case SDLK_s:
					cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, CamSpeed));
					break;
				case SDLK_a:
					cam2D.setPos(cam2D.getPos() + glm::vec2(CamSpeed, 0.0f));
					break;
				case SDLK_d:
					cam2D.setPos(cam2D.getPos() + glm::vec2(-CamSpeed, 0.0f));
					break;
				case SDLK_q:
					cam2D.setScale(cam2D.getScale() + ScalSpeed);
					break;
				case SDLK_e:
					cam2D.setScale(cam2D.getScale() - ScalSpeed);
					break;
				default:
					break;
				}
			}
		}
		cam2D.update();
		hudCam.update();
		drawGame();
	}
}

void MainGame::drawGame()
{


	//set base depth
	glClearDepth(1.0);
	//Clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(35.0f / 255.0f, 130.0f / 255.0f, 117.0f / 255.0f, 1.0f);

	colorP.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textLoc = colorP.getUniformLoc("Textu");
	glUniform1i(textLoc, 0);

	//GLint timeLoc = colorP.getUniformLoc("time");
	//glUniform1f(timeLoc, time);

	GLint pLoc = colorP.getUniformLoc("P");
	glm::mat4 camMatrix = cam2D.getCameraMatrix();
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &(camMatrix[0][0]));
	ColourRGBA8 color;
	color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
	glm::vec4 destRect;
	destRect.x = Ground.getBody()->GetPosition().x - Ground.getDimensions().x / 2.0f;
	destRect.y = Ground.getBody()->GetPosition().y - Ground.getDimensions().y / 2.0f;
	destRect.z = Ground.getDimensions().x;
	destRect.w = Ground.getDimensions().y;
	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 1.0f, color);



	spriteBatch.end();
	spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	map.debugPrintRaw();
	colorP.unuse();
	SDL_GL_SwapWindow(window.gWindow);
}

bool MainGame::compFrontToBack(glm::vec4* a, glm::vec4* b)
{ 
	return (a->w < b->w); 
}

void MainGame::drawHUD()
{
	char buffer[256];
	UIspriteBatch.begin();
	static int fps;
	GLint pLoc = colorP.getUniformLoc("P");
	glm::mat4 camMatrix = hudCam.getCameraMatrix();
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &(camMatrix[0][0]));
	ColourRGBA8 colour = ColourRGBA8(255, 255, 255, 255);
	static int framecounter = 0;
	if (framecounter++ == 20)
	{
		fps = window.getfps();
		framecounter = 0;
	}
	sprintf_s(buffer, "FPS: %d", fps);
	spriteFont->draw(UIspriteBatch, buffer, glm::vec2(20, 20), glm::vec2(1.0f), 0.0f, colour);
	UIspriteBatch.end();
	UIspriteBatch.renderBatch();
}