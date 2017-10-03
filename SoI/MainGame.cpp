#include "MainGame.h"
#include <Engine\Log.h>
#include <iostream>
#include <Engine\SpriteBatch.h>
#include <Engine\ResourceManager.h>
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
		
		std::mt19937 randGenerator (time(NULL));
		std::uniform_real_distribution<float> xPos(-15.0f, 15.0f);
		std::uniform_real_distribution<float> yPos(10.0f, 40.0f);
		std::uniform_real_distribution<float> size(0.5f, 2.5f);
		const int num_box = 100;
		GLTexture texture = ResourceManager::getTexture("Include/Textures/Block.png");
		ColourRGBA8 color;
		for (int i = 0; i < num_box; i++)
		{
			Box *newBox = new Box;
			newBox->init(world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)),texture, color, glm::vec2(size(randGenerator), size(randGenerator)));
			boxes.push_back(newBox);
		}
		Ground.Fixedinit(world.get(), glm::vec2(0.0f, -18.0), dimes);

		ball.init(world.get(), glm::vec2(0.0f, 0.0f), 5.0f);
		GLTexture texturep = ResourceManager::getTexture("Include/Textures/Char.png");
		player.init(world.get(), glm::vec2(6.0f,10.0f), color, texturep, glm::vec2(0.8f,3.0f));

		spriteBatch.init();
		UIspriteBatch.init();
		spriteFont = new SpriteFont("Include/Fonts/font.ttf", 16);

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
	const float CamSpeed = 0.5f;
	const float ScalSpeed = 0.5f;
	bool isforceOn = false;
	//renderDebug = true;
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
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_w:
					cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, -CamSpeed));
					break;
				case SDLK_s :
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
					//boxes[0]->getBody()->ApplyLinearImpulse(b2Vec2{ 0.0f,1.0f }, boxes[0]->getBody()->GetWorldCenter(),true);
					if (isforceOn)
					{
						boxes[0]->getBody()->SetGravityScale(1);
						isforceOn = false;
						boxes[0]->getBody()->SetLinearDamping(0);
					}
					else
					{
						boxes[0]->getBody()->SetGravityScale(0);
						isforceOn = true;
						boxes[0]->getBody()->SetLinearDamping(0.1f);
					}
					
					break;
				default:
					break;
				}
			}
		}
		world->Step(1.0f / 60.f, 6, 2);
		b2Vec2 dir = ball.getBody()->GetPosition() - boxes[0]->getBody()->GetPosition();
		if (isforceOn) boxes[0]->getBody()->ApplyForce(10* dir,boxes[0]->getBody()->GetWorldCenter(), true);
		cam2D.update();
		hudCam.update();
		drawGame();

	}
	//dRender.dispose();
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
	for (auto& b : boxes)
	{
		b->draw(spriteBatch);
		if (b->getIfInSoi())
		{
			b2Vec2 p = -(b->getBody()->GetWorldCenter() - ball.getBody()->GetWorldCenter());
			/*float dist = p.Length();
			float sum = p.x + p.y;
			float last = (1.0f / sum)*100 / dist;
			p.x = p.x * last;
			p.y = p.y * last;*/
			b->getBody()->ApplyForce(9*p, b->getBody()->GetWorldCenter(), true);
		}	
	}
	player.draw(spriteBatch);
	color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
	glm::vec4 destRect;
	destRect.x = Ground.getBody()->GetPosition().x - Ground.getDimensions().x / 2.0f;
	destRect.y = Ground.getBody()->GetPosition().y - Ground.getDimensions().y / 2.0f;
	destRect.z = Ground.getDimensions().x;
	destRect.w = Ground.getDimensions().y;
	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 1.0f, color);
	destRect.x = ball.getBody()->GetPosition().x - ball.getRadius();
	destRect.y = ball.getBody()->GetPosition().y - ball.getRadius();
	destRect.z = ball.getRadius()*2.0f;
	destRect.w = ball.getRadius()*2.0f;
	color.setColour(255.0f, 255.0f, 255.0f, 255.0f);
	static GLTexture texture2 = ResourceManager::getTexture("Include/Textures/rock_type_planet.png");
	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture2.id, 1.0f, color);

	/*glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("Include/Textures/Block.png");
	GLuint id = texture.id;
	spriteBatch.draw(pos, uv, id, 0.0f, color, 45.0f);*/


	spriteBatch.end();
	spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	colorP.unuse();
	
	if (renderDebug)
	{
		glm::vec2 pos;
		pos.x = ball.getBody()->GetPosition().x;
		pos.y = ball.getBody()->GetPosition().y;
		dRender.drawCircle(pos, color, ball.getSoIRadius());
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
