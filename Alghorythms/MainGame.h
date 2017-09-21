#pragma once
#include <Engine/Window.h>
#include <Engine/GLSLProgram.h>
#include <Engine/SpriteBatch.h>
#include <Engine/Camera2D.h>
#include <Box2D/Box2D.h>

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

