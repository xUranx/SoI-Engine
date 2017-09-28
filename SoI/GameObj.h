#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
class GameObj
{
public:
	GameObj();
	virtual ~GameObj();
	virtual void update() = 0;

protected:
	b2Body* body;
	b2Fixture* fixture;
	glm::vec2 dimens;

};

