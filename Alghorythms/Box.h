#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include "CollisionListener.h"
#include <Engine\Log.h>
#include <Engine\SpriteBatch.h>
#include <Engine\GLTexture.h>
class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2 position, Engine::GLTexture text, Engine::ColourRGBA8& color, const glm::vec2& dimensions);

	void Fixedinit(b2World * world, const glm::vec2 position, const glm::vec2 dimensions);

	b2Body* getBody() const { return body; }
	b2Fixture* getFixture() const { return fixture; }
	const glm::vec2 getDimensions() const { return dimens; }
	b2Vec2 getPLPos() const { return PlanetPos; }
	bool getIfInSoi() const { return SoIContact; }

	void startContact() { contact = true; }
	void endContact() { contact = false; }
	void startSoIcontact(b2Vec2 pos) { SoIContact = true; PlanetPos = pos; body->SetGravityScale(0); }
	void endSoIcontact() { SoIContact = false; PlanetPos = b2Vec2(0.0f, 0.0f); body->SetGravityScale(1); }
	void draw(Engine::SpriteBatch& sBatch);
private:
	b2Vec2 PlanetPos = b2Vec2(0.0f,0.0f);
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimens = glm::vec2(0.0f);
	entityCat::entityCatecory eCat = entityCat::Block;
	bool contact = false;
	bool SoIContact = false;
	Engine::GLTexture texture;
	Engine::ColourRGBA8 colour;
};

