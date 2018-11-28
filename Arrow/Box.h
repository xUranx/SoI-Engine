#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include "CollisionListener.h"
#include <Engine\Include\Log.h>
#include <Engine\Include\SpriteBatch.h>
#include <Engine\Include\GLTexture.h>
#include <Engine\Include\Vertex.h>
#include "GameObj.h"
class Box : public GameObj
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2 position, Engine::GLTexture text, Engine::ColourRGBA8& color, const glm::vec2& dimensions);

	void Fixedinit(b2World * world, const glm::vec2 position, const glm::vec2 dimensions);

	void draw(Engine::GLSpriteBatch& sBatch);

	b2Body* getBody() const { return body; }
	b2Fixture* getFixture() const { return fixture; }
	const glm::vec2 getDimensions() const { return dimens; }

	void update() {}

	void collision(b2Fixture* other) {}
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimens = glm::vec2(0.0f);
	entityCat::entityCatecory eCat = entityCat::Block;
	Engine::GLTexture texture;
	Engine::ColourRGBA8 colour;
};

