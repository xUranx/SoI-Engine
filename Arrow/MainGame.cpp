#include "MainGame.h"
#include <Engine\Include\Log.h>
#include <iostream>
#include <Engine\Include\SpriteBatch.h>
#include <Engine\Include\ResourceManager.h>
#include <random>
#include <time.h>
using namespace Engine;
MainGame::MainGame(): xtime(0), sWidth(1024), sHeight(640)
{
}


MainGame::~MainGame()
{
}


void MainGame::run()
{
	if (!window.init("Sphere of Influence", sWidth, sHeight, 0))
	{
		fatal_error("Failed to init window");
	}
	else
	{	
		if(!initShaders())
		{

		}
		
		b2Vec2 grav(0.0f, -9.81);
		glm::vec2 dimes = glm::vec2(50.0f, 3.0f);
		world = std::make_unique<b2World>(grav);
		
		ColourRGBA8 color;

		Ground.Fixedinit(world.get(), glm::vec2(0.0f, -18.0), dimes);

		GLTexture texturep = ResourceManager::getTexture("assets/Textures/Char.png");
		arrowtext = ResourceManager::getTexture("assets/Textures/Arrow.png");
		player.init(world.get(), glm::vec2(6.0f,10.0f), color, texturep, glm::vec2(0.8f,3.0f));

		spriteBatch.init();
		UIspriteBatch.init();
		spriteFont = new SpriteFont("assets/Fonts/font.ttf", 16);

		cam2D.init(sWidth, sHeight);
		hudCam.init(sWidth, sHeight);

		//cam2D.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
		hudCam.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
		cam2D.setScale(18.0f);

		dRender.init();

		world->SetContactListener(&ColList);

		gLoop();
	}

	//Free resources and close SDL

	//boxes.clear();
	window.close();
}

bool MainGame::initShaders()
{
	bool success = true;
	success = colorP.compileShaders("assets/Shaders/colorShading.vert", "assets/Shaders/colorShading.frag");
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
	bool isforceOn = false;
	renderDebug = false;
	bool isPressed = false;
	while (!quit)
	{
		xtime += 0.01;
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
			if (e.type == SDL_MOUSEMOTION)
			{
				mouse = cam2D.TranslateScreenToWorld(e.motion.x, e.motion.y);
			}
		
		}
		processInput();
		if (inputManager.isKeyPressed(SDLK_ESCAPE)) quit = true;
		world->Step(1.0f / 60.f, 6, 2);
		glm::vec2 pos = { player.getBox().getBody()->GetPosition().x,
						  player.getBox().getBody()->GetPosition().y };
		glm::vec2 direction = mouse - pos;
		float angle = atan2f(-direction.x, direction.y);

		if (inputManager.isKeyPressed(SDLK_k)&&!isPressed)
		{
			ColourRGBA8 color;
			Arrow* n_arrow = new Arrow;
			n_arrow->Init(world.get(), player.getBox().getBody(), arrowtext, color, angle, 20.f);
			m_arrow_list.push_back(n_arrow);
			isPressed = true;
		}
		else if (inputManager.isKeyPressed(SDLK_k))
		{

		}
		else
		{
			isPressed = false;
		}

		for (auto arrow : m_arrow_list)
		{
			arrow->update();
		}

		cam2D.update();
		hudCam.update();
		drawGame();

	}
	//dRender.dispose();
}

void MainGame::processInput()
{
	const float CamSpeed = 0.2f;
	const float ScalSpeed = 0.2f;
	static float dir;
	if (inputManager.isKeyPressed(SDLK_s)) cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, -CamSpeed));

	if (inputManager.isKeyPressed(SDLK_w)) cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, CamSpeed));

	if (inputManager.isKeyPressed(SDLK_d))
		cam2D.setPos(cam2D.getPos() + glm::vec2(CamSpeed, 0.0f));
	if (inputManager.isKeyPressed(SDLK_a))
		cam2D.setPos(cam2D.getPos() + glm::vec2(-CamSpeed, 0.0f));
	if (inputManager.isKeyPressed(SDLK_q))
		cam2D.setScale(cam2D.getScale() + ScalSpeed);
	if (inputManager.isKeyPressed(SDLK_e))
		cam2D.setScale(cam2D.getScale() - ScalSpeed);
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

	glm::mat4 camMatrix = cam2D.getCameraMatrix();
	GLint pLoc = colorP.getUniformLoc("P");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, &(camMatrix[0][0]));

	spriteBatch.begin();
	
	ColourRGBA8 color;

	player.draw(spriteBatch);
	color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
	glm::vec4 destRect;
	destRect.x = Ground.getBody()->GetPosition().x - Ground.getDimensions().x / 2.0f;
	destRect.y = Ground.getBody()->GetPosition().y - Ground.getDimensions().y / 2.0f;
	destRect.z = Ground.getDimensions().x;
	destRect.w = Ground.getDimensions().y;
	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 1.0f, color);
	color.setColour(255.0f, 255.0f, 255.0f, 255.0f);

	/*destRect = { mouse,1,1 };
	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 1.0f, color);*/

	/*glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("assets/Textures/Block.png");
	GLuint id = texture.id;
	spriteBatch.draw(pos, uv, id, 0.0f, color, 45.0f);*/

	for (auto arrow : m_arrow_list)
	{
		arrow->Draw(spriteBatch);
	}

	spriteBatch.end();
	spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	colorP.unuse();
	
	if (renderDebug)
	{
		glm::vec2 pos;
		//dRender.drawCircle(glm::vec2(b.getBody()->GetPosition().x, b.getBody()->GetPosition().y), color, b.getDimensions().x / 2.0f);
		dRender.end();
		dRender.render(camMatrix, 2.0f);
	}

	SDL_GL_SwapWindow(window.gWindow);
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
	sprintf_s(buffer, "FPS: %d" ,fps);
	spriteFont->draw(UIspriteBatch, buffer, glm::vec2(0, sHeight-20), glm::vec2(1.0f), 0.0f, colour);
	UIspriteBatch.end();
	UIspriteBatch.renderBatch();
}
