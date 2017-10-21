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
			spriteBatchTri.init();
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
	cam2D.setScale(18.0f);
	//Event handler
	SDL_Event e;
	//map.init("Level1", 20, 200);
	//map.genMapData(world.get(), glm::vec2(0, 0), 4);
	glm::vec2 dim[3];
	dim[0].x = -2.0f;
	dim[0].y = -2.0f;
	dim[1].x = 0.0f;
	dim[1].y = 2.0f;
	dim[2].x = 2.0f;
	dim[2].y = -2.0f;
	ship.init(world.get(), glm::vec2(0, 15), dim, false, 0.5f);
	GLTexture texture = ResourceManager::getTexture("../SoI/Include/Textures/Block.png");
	ColourRGBA8 color;
	box.init(world.get(), glm::vec2(3.0f, 0.0f),texture,color, glm::vec2(5, 5));
	const float CamSpeed = 0.5f;
	const float ScalSpeed = 0.5f;
	int val = 1;
	//While application is running
	bool sorted = false;
	bool force = false;
	while (!quit)
	{
		window.fpsCounter();
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
				inputManager.pressKey(e.key.keysym.sym);
			}
			if (e.type == SDL_KEYUP)
			{
				inputManager.releaseKey(e.key.keysym.sym);
			}
		}

		if (inputManager.isKeyPressed(SDLK_ESCAPE)) quit = true;

		if (force) ship.getBody()->ApplyForce(50 * ship.getBody()->GetWorldVector(b2Vec2(0, 1)), ship.getBody()->GetWorldPoint(b2Vec2(0,-1)), true);
		float mass = ship.getBody()->GetMass();
		world->Step(1.0f / 60.f, 6, 2);
		cam2D.update();
		hudCam.update();
		drawGame();
	}
}

void MainGame::processInput()
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
	case SDLK_x:
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

	spriteBatch.begin();

	ColourRGBA8 color;
	color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
	glm::vec4 destRect;
	destRect.x = Ground.getBody()->GetPosition().x - Ground.getDimensions().x / 2.0f;
	destRect.y = Ground.getBody()->GetPosition().y - Ground.getDimensions().y / 2.0f;
	destRect.z = Ground.getDimensions().x;
	destRect.w = Ground.getDimensions().y;
	box.draw(spriteBatch);
	//map.draw(spriteBatch);
	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 0.0f, color);
	ship.draw(spriteBatch);
	spriteBatch.end();
	spriteBatch.renderBatch();
	//map.debugPrintRaw();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
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