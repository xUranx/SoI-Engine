#pragma once
#include <Engine/Window.h>
#include <Engine/Sprite.h>
#include <Engine\GLSLProgram.h>

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
	Window window{"Sphere Of Influence"};
	Sprite _sprite;
	void drawGame();

	GLSLProgram colorP;
};

