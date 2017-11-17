#include "MainGame.h"
#include <Engine\Include\Log.h>
#include <Engine\Include\ResourceManager.h>
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
	success = colorP.compileShaders("../SoI/Assets/Shaders/colorShading.vert", "../SoI/Assets/Shaders/colorShading.frag");
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
	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> Height(20.0f, 300.0f);
	int nums = (sWidth);
	float posX = 0.0f;
	for (int i = 0; i < nums; i++)
	{
		glm::vec4 p(posX++, 0.0f, 1.0f, Height(randGenerator));
		pos.push_back(p);
	}
	posP.resize(pos.size());
	for (int i = 0; i < pos.size(); i++)
	{
		posP[i] = &pos[i];
	}
	Message("Generated New Data");
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
				case SDLK_s:
					if (!sorted)
					{
						posP.resize(pos.size());
						for (int i = 0; i < pos.size(); i++)
						{
							posP[i] = &pos[i];
						}
						std::stable_sort(posP.begin(), posP.end(), compFrontToBack);
						posX = 1.0f;
						for (int i = 0; i < posP.size(); i++)
						{
							posP[i]->x = posX++;
						}
						Message("Sorted");
						sorted = true;
					}
					break;
				case SDLK_r:
					posX = 1.0f;
					pos.clear();
					posP.clear();
					for (int i = 0; i < nums; i++)
					{
						glm::vec4 p(posX++, 0.0f, 1.0f, Height(randGenerator));
						pos.push_back(p);
					}
					posP.resize(pos.size());
					for (int i = 0; i < pos.size(); i++)
					{
						posP[i] = &pos[i];
					}
					Message("Generated New Data");
					sorted = false;
					break;
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

	spriteBatch.begin();
	//static GLTexture texture = ResourceManager::getTexture("assets/Textures/Block.png");
	ColourRGBA8 color = { 255, 255, 255, 255 };
	//for (auto& b : boxes)
	//{
	//	glm::vec4 destRect;
	//	destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2.0f;
	//	destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2.0f;
	//	destRect.z = b.getDimensions().x;
	//	destRect.w = b.getDimensions().y;
	//	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 0.0f, color, b.getBody()->GetAngle());
	//}
	
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("../SoI/Include/Textures/Block.png");
	for (int i = 0; i < posP.size(); i++)
	{
		spriteBatch.draw(*posP[i], uv, NULL, 0.0f, color);
	}
	

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