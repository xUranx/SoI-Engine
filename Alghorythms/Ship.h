#pragma once
#include <glm\glm.hpp>
#include <Box2D\Box2D.h>
#include <Engine\SpriteBatch.h>
class Thruster
{
public:
	Thruster();
	~Thruster();
	b2FixtureDef init(bool rand);
	void TogglePower() { if (power)power = false; else power = true; }
	void draw(Engine::SpriteBatch sBatch);
	void setFixture(b2Fixture* fixt) { fixture = fixt; }
private:
	b2Fixture* fixture = nullptr;
	bool power = false;
	float thrust  = 0;
	glm::vec2 gimbal = glm::vec2(0,1);
};

class Ship
{
public:
	Ship();
	~Ship();
	void init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions[], bool rand);
	void draw(Engine::SpriteBatch sBatch);
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	b2Vec2 dimens[3];
	Thruster thruster;
};

