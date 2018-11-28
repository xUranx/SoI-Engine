#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
class GameObj
{
public:
	GameObj();
	~GameObj();
	virtual void update() = 0;
	void startContact() { contact = true; }
	void endContact() { contact = false; }
	virtual void collision(b2Fixture*) = 0;
protected:
	bool contact = false;

};

