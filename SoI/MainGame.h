#pragma once
#include <Engine/Window.h>
#include <Engine/Sprite.h>
#include <Engine/GLSLProgram.h>
#include <Engine/Camera2D.h>
#include <Engine/SpriteBatch.h>
#include <Box2D\Box2D.h>
#include "Box.h"
#include <vector>
#include "Planet.h"

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
	int sWidth, sHeight;
	Engine::Camera2D cam2D;
	void gLoop();
	Engine::Window window;
	//std::vector<Engine::Sprite*> _sprite;
	void drawGame();
	float time;
	Engine::GLSLProgram colorP;
	std::unique_ptr<b2World> world;
	std::vector<Box> boxes;
	Engine::SpriteBatch spriteBatch;
	Box Ground;
	Planet ball;
};

