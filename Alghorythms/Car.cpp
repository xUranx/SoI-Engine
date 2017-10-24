#include "Car.h"

Tire::Tire()
{
}

Tire::~Tire()
{
}


Car::Car()
{
}


Car::~Car()
{
}

void Car::init(b2World * wordl, glm::vec2 Pos)
{
	b2BodyDef bDef;
	bDef.position.Set(Pos.x, Pos.y);
	bDef.type = b2_dynamicBody;
	body = wordl->CreateBody(&bDef);


}

