#include "Planet.h"
#include "CollisionListener.h"


Planet::Planet()
{
}


Planet::~Planet()
{
}

void Planet::init(b2World * world, const glm::vec2 position, const float Rad)
{
	color.setColour(255, 255, 255, 255);
	radius = Rad;
	b2BodyDef bDef;
	bDef.type = b2_staticBody;
	bDef.position.Set(position.x, position.y);

	body = world->CreateBody(&bDef);
	b2CircleShape bCShape;

	bCShape.m_p.Set(0.0f, 0.0f);
	bCShape.m_radius = radius;

	b2FixtureDef fDef;
	fDef.density = 1.0f;
	fDef.friction = 1.0f;
	fDef.shape = &bCShape;
	fixture = body->CreateFixture(&fDef);

	//SoI Senseor
	b2CircleShape circleShape;
	circleShape.m_radius = Rad + 2.0f;
	fDef.shape = &circleShape;
	fDef.isSensor = true;
	fDef.filter.categoryBits = entityCat::Planet_SOI;
	fDef.filter.maskBits = entityCat::Block;
	sFixture = body->CreateFixture(&fDef);
	body->SetUserData(this);
}
