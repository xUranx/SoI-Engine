#include "Planet.h"



Planet::Planet()
{
}


Planet::~Planet()
{
}

void Planet::init(b2World * world, const glm::vec2 position, const float Rad)
{
	radius = Rad;
	b2BodyDef bDef;
	bDef.position.Set(position.x, position.y);

	body = world->CreateBody(&bDef);
	b2CircleShape bCShape;
	bCShape.m_p.Set(0.0f, 0.0f);
	bCShape.m_radius = radius;
	body->CreateFixture(&bCShape, 0.0f);
}
