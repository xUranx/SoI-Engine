#pragma once
#include <Engine\Include\/Window.h>
#include <Engine\Include\/Sprite.h>
#include <Engine\Include\/GLSLProgram.h>
#include <Engine\Include\/Camera2D.h>
#include <Engine\Include\/SpriteBatch.h>
#include <Engine\Include\/SpriteFont.h>
#include <Engine\Include\/DebugRenderer.h>
#include <Engine\Include\/InputManager.h>
#include <Box2D\Box2D.h>
#include "Box.h"
#include <vector>
#include "Planet.h"
#include "Player.h"
#include "CollisionListener.h"

enum GameState
{
	MainMenu, Game, Exit 
};

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
	bool initShaders();
private:
	bool renderDebug = true;
	int sWidth, sHeight;
	void gLoop();
	//std::vector<Engine\Include\::Sprite*> _sprite;
	void drawGame();
	void processInput();
	void drawHUD();
	float xtime;
	Engine::Camera2D cam2D;
	Engine::Camera2D hudCam;
	Engine::Window window;
	Engine::GLSLProgram colorP;
	Engine::SpriteBatch spriteBatch;
	Engine::SpriteBatch UIspriteBatch;
	Engine::SpriteFont* spriteFont;
	Engine::DebugRenderer dRender;
	Engine::InputManager inputManager;
	CollisionListener ColList;
	std::unique_ptr<b2World> world;
	std::vector<Box*> boxes;
	Box Ground;
	Planet ball;
	Player player;
};

