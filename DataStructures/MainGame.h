#pragma once
#include <Engine\Include\/Window.h>
#include <Engine\Include\/GLSLProgram.h>
#include <Engine\Include\/SpriteBatch.h>
#include <Engine\Include\/Camera2D.h>

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
	int sWidth;
	int sHeight;
	void gLoop();
	bool initShaders();
	void drawGame();
	Engine::Window window;
	Engine::GLSLProgram colorP;
	Engine::SpriteBatch spriteBatch;
	Engine::Camera2D cam2D;
	std::vector<glm::vec4> pos;
	std::vector<glm::vec4*> posP;
	static bool compFrontToBack(glm::vec4* a, glm::vec4* b);
	
		

};

