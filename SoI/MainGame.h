#pragma once
#include <Engine/Window.h>
#include <Engine/Sprite.h>

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
private:
	void gLoop();
	Window window{"Sphere Of Influence"};
	Sprite _sprite;
	void drawGame();
};

