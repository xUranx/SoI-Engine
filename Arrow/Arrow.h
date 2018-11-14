#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/Vertex.h>
#include <Engine/Include/SpriteBatch.h>
#include "CollisionListener.h"
#include <Engine\Include\Log.h>

class Arrow
{
public:
	Arrow();
	~Arrow();

	void Init(b2World * world, b2Body*, Engine::GLTexture text, Engine::ColourRGBA8& color, float angle, float sVel);

	void update();

	void Draw(Engine::GLSpriteBatch&);
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	entityCat::entityCatecory eCat = entityCat::Block;
	bool contact = false;
	bool SoIContact = false;
	Engine::GLTexture texture;
	Engine::ColourRGBA8 colour;
};

