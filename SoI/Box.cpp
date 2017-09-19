#include "Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 position, const glm::vec2& dimensions)
{
	dimens = dimensions;
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(position.x, position.y);

	body = world->CreateBody(&bDef);

	b2PolygonShape bShape;
	bShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fDef;
	fDef.shape = &bShape;
	fDef.density = 1.0f;
	fDef.friction = 0.3f;

	fixture = body->CreateFixture(&fDef);
}
void Box::Fixedinit(b2World * world, const glm::vec2 position, const glm::vec2 dimensions)
{
	dimens = dimensions;
	b2BodyDef bDef;
	bDef.position.Set(position.x, position.y);

	body = world->CreateBody(&bDef);

	b2PolygonShape bShape;
	bShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	body->CreateFixture(&bShape, 0.0f);
}
