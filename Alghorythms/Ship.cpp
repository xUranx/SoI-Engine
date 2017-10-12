#include "Ship.h"
#include "CollisionListener.h"

using namespace entityCat;

Thruster::Thruster()
{
}

Thruster::~Thruster()
{
}


Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions[],bool rand)
{
	dimens[0].x = dimensions[0].x;
	dimens[0].y = dimensions[0].y;
	dimens[1].x = dimensions[1].x;
	dimens[1].y = dimensions[1].y;
	dimens[2].x = dimensions[2].x;
	dimens[2].y = dimensions[2].y;
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(position.x, position.y);

	body = world->CreateBody(&bDef);

	b2PolygonShape pShape;
	pShape.Set(dimens, 5);

	b2FixtureDef fDef;
	fDef.shape = &pShape;
	fDef.density = 1.0f;
	fDef.friction = 0.3f;
	fDef.filter.categoryBits = Player;
	fDef.filter.maskBits = Walls;
	fixture = body->CreateFixture(&fDef);
	//thruster.setFixture(body->CreateFixture(&thruster.init(rand)));
	body->SetUserData(this);
}