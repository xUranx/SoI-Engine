#pragma once
#include <Engine/Window.h>
#include <Engine/GLSLProgram.h>
#include <Engine/SpriteBatch.h>
#include <Engine/Camera2D.h>
#include <Engine/SpriteFont.h>
#include <Engine/InputManager.h>
#include <Engine/DebugRenderer.h>
#include <Box2D/Box2D.h>
#include "Level.h"
#include "Box.h"
#include "Ship.h"
#include "GATextDemo.h" 
enum GameState
{
	MainMenu, Game, Text, Exit 
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
};

