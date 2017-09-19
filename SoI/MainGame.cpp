#include "MainGame.h"
#include <Engine\Log.h>
#include <iostream>
#include <Engine\SpriteBatch.h>
#include <Engine\ResourceManager.h>
#include <random>
using namespace Engine;
MainGame::MainGame(): time(0), sWidth(1024), sHeight(640)
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
			goto errorend;
		}
		b2Vec2 grav(0.0f, -9.81);
		glm::vec2 dimes = glm::vec2(50.0f, 5.0f);
		world = std::make_unique<b2World>(grav);
		Ground.Fixedinit(world.get(), glm::vec2(0.0f, -15.0), dimes);
		/*b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -20.0f);
		b2Body* groundBody = world->CreateBody(&groundBodyDef);
		b2PolygonShape gBox;
		gBox.SetAsBox(50.0f, 10.0f);
		groundBody->CreateFixture(&gBox, 0.0f);*/
		std::mt19937 randGenerator;
		std::uniform_real_distribution<float> xPos(-10.0f, 10.0f);
		std::uniform_real_distribution<float> yPos(0.0f, 20.0f);
		std::uniform_real_distribution<float> size(0.5f, 2.5f);
		const int num_box = 10;
		for (int i = 0; i < num_box; i++)
		{
			Box newBox;
			newBox.init(world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(size(randGenerator), size(randGenerator)));
			boxes.push_back(newBox);
		}
		ball.init(world.get(), glm::vec2(0.0f, 0.0f), 2.0f);
		spriteBatch.init();

		cam2D.init(sWidth, sHeight);
		//cam2D.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
		cam2D.setScale(18.0f);
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
	const float CamSpeed = 0.5f;
	const float ScalSpeed = 0.5f;
	while (!quit)
	{
		time += 0.01;
		window.fpsCounter();
		static int framecounter = 0;
		if (framecounter++ == 10)
		{
			std::cout << window.getfps() << std::endl;
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
					boxes[0].getBody()->ApplyLinearImpulse(b2Vec2{ 0.0f,50.0f }, boxes[0].getBody()->GetWorldCenter(),true);
					break;
				default:
					break;
				}
			}
		}
		world->Step(1.0f / 60.f, 6, 2);
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
	static GLTexture texture = ResourceManager::getTexture("Include/Textures/Block.png");
	ColourRGBA8 color;
	for (auto& b : boxes)
	{
		glm::vec4 destRect;
		destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x/2.0f;
		destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y/2.0f;
		destRect.z = b.getDimensions().x;
		destRect.w = b.getDimensions().y;
		spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, color, b.getBody()->GetAngle());
	}
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
	glBindTexture(GL_TEXTURE_2D, 0);
	colorP.unuse();

	SDL_GL_SwapWindow(window.gWindow);
}
