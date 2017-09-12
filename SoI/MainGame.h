#pragma once
#include "Window.h"

enum GameState
{
	MainMenu, Game, Exit 
};

class MainGame: public Window
{
public:
	MainGame();
	~MainGame();
	void run();
private:
	void gLoop();
	Window window;
};

