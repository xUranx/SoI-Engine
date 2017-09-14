#pragma once
#include <Engine/Window.h>
#include <Engine/Sprite.h>
#include <Engine/GLSLProgram.h>
#include <vector>

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
	void gLoop();
	Window window;
	std::vector<Sprite*> _sprite;
	void drawGame();
	float time;
	GLSLProgram colorP;
	
};

