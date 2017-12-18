#include "MainGame.h"
#include <Engine/Include/Log.h>
#include <Engine/Include/ResourceManager.h>
#include <random>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <Engine/Include/IOManager.h>
#ifndef WIN32
#include <graphics/GraphicsSystem.h>
#include <graphics/Window.h>
#include <core/Log.h>

#endif

using namespace Engine;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

MainGame::MainGame()
{
	sWidth = 1024;
	sHeight = 640;
}


MainGame::~MainGame()
{
}
#ifdef WIN32
void MainGame::run()
#else
void MainGame::run(engine::Window* swindow)
#endif
{
#ifdef WIN32
	if (!window.init("Genetic Algorithm", sWidth, sHeight, 0))
	{
		fatal_error("Failed to Init");
	}
#else
    sWidth = swindow->getWidth();
	sHeight = swindow->getHeight();
    LOGE("Widht: %d" , sWidth);
    LOGE("Height: %d" , sHeight);
    m_window = swindow;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
		//Load media
	if (!initShaders())
	{
		fatal_error("Failed to init shaders");
	}
			
		spriteBatch.init();
		//spriteBatchTri.init();
		UIspriteBatch.init();
#ifdef WIN32
		spriteFont = new SpriteFont("assets/Fonts/OpenSansRegular.ttf", 32);
#endif // WIN32
		//dRender.init();
		gLoop();
	
	//Free resources and close SDL
#ifdef WIN32
	window.close();
#endif // WIN32
}

bool MainGame::initShaders()
{
	/*std::string sysName = SDL_GetPlatform();
	Message(sysName);*/
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
	bool init = true;
	//renderDebug = true;
	cam2D.init(sWidth,sHeight);
	hudCam.init(sWidth, sHeight);
	//cam2D.setPos(cam2D.getPos() + glm::vec2(sWidth / 2.0f, sHeight / 2.0f));
    glm::vec2 pss = glm::vec2(cam2D.getPos().x + sWidth / 2.0f, cam2D.getPos().y + sHeight / 2.0f);
	hudCam.setPos(pss);
	gMode = GCar;

	//Event handler
#ifdef WIN32
	SDL_Event e;
#endif
	const float CamSpeed = 0.5f;
	const float ScalSpeed = 0.5f;
	int val = 1;
	//While application is running
	while (gMode != Exit)
	{
#ifdef WIN32
		window.fpsCounter();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				gMode = Exit;
			}
			if (e.type == SDL_KEYDOWN)
			{
				inputManager.pressKey(e.key.keysym.sym);
			}
			if (e.type == SDL_KEYUP)
			{
				inputManager.releaseKey(e.key.keysym.sym);
			}
			if (e.type = SDL_MOUSEMOTION)
			{
				int mouseX = e.motion.x;
				int mouseY = e.motion.y;
			}
		}
		
		if (inputManager.isKeyPressed(SDLK_ESCAPE)) gMode = Exit;
#endif // WIN32
		switch (gMode)
		{
		case Game: {
            if (init) {
                b2Vec2 grav(0.0f, -9.81);
                world = new b2World(grav);
                glm::vec2 dimes = glm::vec2(50.0f, 3.0f);
                Ground.Fixedinit(world, glm::vec2(0.0f, -15.0f), dimes);
                cam2D.setScale(30.0f);
                init = false;
                map.init("Level1", 20, 200);
                map.genMapData(world, glm::vec2(0, 0), 5);
                glm::vec2 dim[3];
                dim[0].x = -1.5f;
                dim[0].y = -2.0f;
                dim[1].x = 0.0f;
                dim[1].y = 2.0f;
                dim[2].x = 1.5f;
                dim[2].y = -2.0f;
                ship.init(world, glm::vec2(21, 5), dim, false, 0.4f);
                GLTexture texture = ResourceManager::getTexture("Assets/Textures/Block.png");
                ColourRGBA8 color;
                //box.init(world.get(), glm::vec2(3.0f, 0.0f),texture,color, glm::vec2(5, 5));


            }
            ship.raycast();
            glm::vec2 psss = glm::vec2(ship.getBody()->GetPosition().x,
                                       ship.getBody()->GetPosition().y);
            cam2D.setPos(pss);
#ifdef WIN32
            processInput();
#endif
            world->Step(1.0f / 60.f, 6, 2);
            if (nMode != Game && nMode != NULL) {
                delete (&world);
                world = nullptr;
                gMode = nMode;
            }
            break;
        }
		case GCar: {
            if (init) {
                init = false;
                b2Vec2 grav(0.0f, -9.81);
                world = new b2World(grav);
				glm::vec2 dimes = glm::vec2(300.0f, 3.0f);
                Ground.Fixedinit(world, glm::vec2(140.0f, -15.0f), dimes);
                Evo.init(world);
                //car.init(world.get(), glm::vec2(0, -13));
                cam2D.setScale(24.0f);
            }
            Evo.run(cam2D);
            //cam2D.setPos(glm::vec2(car.getBody()->GetPosition().x, car.getBody()->GetPosition().y));
            world->Step(1.0f / 60.f, 6, 2);
            break;
        }
		case Text: {
            if (init) {
                init = false;
                test.start();
            }


            if (!test.getSegFound()) {
                test.run();
            }

            if (nMode != Text && nMode != NULL) {
                delete (&test);
                gMode = nMode;
            }
            break;
        }
		}


		//cam2D.setPos(glm::vec2(ship.getBody()->GetPosition().x, ship.getBody()->GetPosition().y));

		cam2D.update();
		hudCam.update();
		drawGame();
	}
}
#ifdef WIN32


void MainGame::processInput()
{
	if (gMode == Game)
	{
	const float CamSpeed = 0.2f;
	const float ScalSpeed = 0.2f;
	static float dir;
	if(inputManager.isKeyPressed(SDLK_w)) cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, -CamSpeed));
		
	if (inputManager.isKeyPressed(SDLK_s)) cam2D.setPos(cam2D.getPos() + glm::vec2(0.0f, CamSpeed));
		
	if (inputManager.isKeyPressed(SDLK_a))
		cam2D.setPos(cam2D.getPos() + glm::vec2(CamSpeed, 0.0f));
	if (inputManager.isKeyPressed(SDLK_d))
		cam2D.setPos(cam2D.getPos() + glm::vec2(-CamSpeed, 0.0f));
	if (inputManager.isKeyPressed(SDLK_q))
		cam2D.setScale(cam2D.getScale() + ScalSpeed);
	if (inputManager.isKeyPressed(SDLK_e))
		cam2D.setScale(cam2D.getScale() - ScalSpeed);
		if (inputManager.isKeyPressed(SDLK_z))
			dir = 0.05f;
		else if (inputManager.isKeyPressed(SDLK_c))
			dir = -0.05f;
		else
			dir = 0.0f;
		if (inputManager.isKeyPressed(SDLK_x))
			ship.getBody()->ApplyForce(40 * ship.getBody()->GetWorldVector(b2Vec2(0.0f + dir, 1)), ship.getBody()->GetWorldPoint(b2Vec2(0, -1)), true);
		if (inputManager.isKeyPressed(SDLK_j))
			ship.getBody()->SetTransform(ship.getBody()->GetPosition(), 0);
	}
}
#endif // WIN32

void MainGame::drawGame()
{

	//set base depth
#ifdef WIN32
    glClearDepth(1.0);
#else
    glClearDepthf(1.0);
#endif

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
	if (gMode == MainMenu)
	{

	}
	else if (gMode == Game)
	{
		ColourRGBA8 color;
		color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
		glm::vec4 destRect;
		destRect.x = Ground.getBody()->GetPosition().x - Ground.getDimensions().x / 2.0f;
		destRect.y = Ground.getBody()->GetPosition().y - Ground.getDimensions().y / 2.0f;
		destRect.z = Ground.getDimensions().x;
		destRect.w = Ground.getDimensions().y;
		//box.draw(spriteBatch);
		map.draw(spriteBatch);
		glm::vec4 um = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		spriteBatch.draw(destRect, um, 0, 0.0f, color);
		ship.draw(spriteBatch);
		//map.debugPrintRaw();
	}
	if (gMode == GCar)
	{
		ColourRGBA8 color;
		color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
		glm::vec4 destRect;
		destRect.x = Ground.getBody()->GetPosition().x - Ground.getDimensions().x / 2.0f;
		destRect.y = Ground.getBody()->GetPosition().y - Ground.getDimensions().y / 2.0f;
		destRect.z = Ground.getDimensions().x;
		destRect.w = Ground.getDimensions().y;
		spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0, 0.0f, color);
		//car.draw(spriteBatch);
		Evo.draw(spriteBatch);
	}
	spriteBatch.end();
	spriteBatch.renderBatch();
#ifdef WIN32
	drawHUD();
#endif // WIN32
	glBindTexture(GL_TEXTURE_2D, 0);
	colorP.unuse();

	if (renderDebug)
	{
		if (gMode == Game)
		{
			ship.debugDraw(dRender);
		}
		dRender.end();
		dRender.render(camMatrix, 2.0f);
	}
#ifdef WIN32
	SDL_GL_SwapWindow(window.gWindow);
#else
    m_window->getGraphics()->swapBuffers();
#endif
}

bool MainGame::compFrontToBack(glm::vec4* a, glm::vec4* b)
{ 
	return (a->w < b->w); 
}
#ifdef WIN32


void MainGame::drawHUD()
{
	char buffer[256];
	char buffer2[256];
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
	if (gMode == Text)
	{
		test.print(UIspriteBatch, *spriteFont);
	}
	sprintf_s(buffer, "FPS: %d", fps);
	spriteFont->draw(UIspriteBatch, buffer, glm::vec2(10, 8), glm::vec2(1.0f), 0.0f, colour);
	if (gMode == Game)
	{
		sprintf_s(buffer2, "Angle: %f", ship.getBody()->GetAngle() * RADTODEG);
		spriteFont->draw(UIspriteBatch, buffer2, glm::vec2(10, 40), glm::vec2(1.0f), 0.0f, colour);
	}
	else if (gMode == GCar)
	{
		Evo.print(UIspriteBatch, *spriteFont);
	}
	UIspriteBatch.end();
	UIspriteBatch.renderBatch();
}
#endif // WIN32