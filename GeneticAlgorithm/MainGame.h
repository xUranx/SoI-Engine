#pragma once
#include <Engine\Include\/Window.h>
#include <Engine\Include\/GLSLProgram.h>
#include <Engine\Include\/SpriteBatch.h>
#include <Engine\Include\/Camera2D.h>
#include <Engine\Include\/SpriteFont.h>
#include <Engine\Include\/InputManager.h>
#include <Engine\Include\/DebugRenderer.h>
#include <Box2D/Box2D.h>
#include "Level.h"
#include "Box.h"
#include "Ship.h"
#include "GATextDemo.h" 
#include "Car.h"
#include "GACar.h"
enum GameState
{
	MainMenu, Game, Text, GCar, Exit
};

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
private:
	int sWidth;
	int sHeight;
	void gLoop();
	void processInput();
	bool initShaders();
	void drawGame();
	void drawHUD();
	Engine::Window window;
	Engine::GLSLProgram colorP;
	Engine::SpriteBatch spriteBatch;
	Engine::SpriteBatch spriteBatchTri;
	Engine::SpriteBatch UIspriteBatch;
	Engine::SpriteFont* spriteFont;
	Engine::Camera2D cam2D;
	Engine::Camera2D hudCam;
	Engine::InputManager inputManager;
	Engine::DebugRenderer dRender;
	std::unique_ptr<b2World> world;
	Box Ground;
	Car car;
	std::vector<glm::vec4> pos;
	std::vector<glm::vec4*> posP;
	static bool compFrontToBack(glm::vec4* a, glm::vec4* b);
	bool renderDebug = false;
	Level map;
	Ship ship;
	Box box;
	GameState gMode;
	GameState nMode;
	GATextDemo test;
	GACar Evo;
};

