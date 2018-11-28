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
#include "Player.h"
#include "CollisionListener.h"
#include "Arrow.h"
#include <set>

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
	Engine::GLSpriteBatch spriteBatch;
	Engine::GLSpriteBatch UIspriteBatch;
	Engine::SpriteFont* spriteFont;
	Engine::DebugRenderer dRender;
	Engine::InputManager inputManager;
	std::vector<Arrow*> m_arrow_list;
	std::set<Arrow*> Removal;
	Engine::GLTexture arrowtext;
	CollisionListener ColList;
	std::unique_ptr<b2World> world;
	Box Ground;
	Box Wall;
	Player player;
	glm::vec2 mouse;
};

