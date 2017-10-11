#pragma once
#include <glm\glm.hpp>
#include <Box2D\Box2D.h>
class Engine
{
public:
	Engine();
	~Engine();
	void init();
	void TogglePower() { if (power)power = false; else power = true; }

private:
	bool power = false;
	float thrust  = 0;
	glm::vec2 gimbal = glm::vec2(0,1);
};

class Ship
{
public:
	Ship();
	~Ship();
	void init(b2World* world);
private:
	b2Body* body = nullptr;
};

