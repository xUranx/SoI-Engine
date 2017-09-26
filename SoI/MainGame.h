#pragma once
#include <Engine/Window.h>
#include <Engine/Sprite.h>
#include <Engine/GLSLProgram.h>
#include <Engine/Camera2D.h>
#include <Engine/SpriteBatch.h>
#include <Engine/SpriteFont.h>
#include <Engine/DebugRenderer.h>
#include <Box2D\Box2D.h>
#include "Box.h"
#include <vector>
#include "Planet.h"
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
	//std::vector<Engine::Sprite*> _sprite;
	void drawGame();
	void drawHUD();
	float time;
	Engine::Camera2D cam2D;
	Engine::Camera2D hudCam;
	Engine::Window window;
	Engine::GLSLProgram colorP;
	Engine::SpriteBatch spriteBatch;
	Engine::SpriteBatch UIspriteBatch;
	Engine::SpriteFont* spriteFont;
	Engine::DebugRenderer dRender;
	CollisionListener ColList;
	std::unique_ptr<b2World> world;
	std::vector<Box*> boxes;
	Box Ground;
	Planet ball;
};

