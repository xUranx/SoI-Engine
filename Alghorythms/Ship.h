#pragma once
#include <glm\glm.hpp>
#include <Box2D\Box2D.h>
#include <Engine\SpriteBatch.h>
#include "poly2tri/poly2tri.h"
class Thruster
{
public:
	Thruster();
	~Thruster();
	b2FixtureDef init(bool rand, b2Body* b, float scale);
	//void TogglePower() { if (power)power = false; else power = true; }
	void draw(Engine::SpriteBatch& sBatch, b2Body* body);
	void setFixture(b2Fixture* fixt) { fixture = fixt; }
	b2Fixture* getFixture() const { return fixture; }
private:
	b2Vec2 dimens[6];
	b2Vec2 offset;
	b2Fixture* fixture = nullptr;
	//bool power = false;
	float thrust  = 0;
	glm::vec2 gimbal = glm::vec2(0,1);
	std::vector<p2t::Triangle*> triangles;
};

class Ship
{
public:
	Ship();
	~Ship();
	void init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions[], bool rand, float scale);
	void draw(Engine::SpriteBatch& sBatch);
	void TogglePower() { if (power)power = false; else power = true; }
	b2Body* getBody() { return body; }
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	b2Vec2 dimens[3];
	Thruster thruster;
	bool power = false;
};

