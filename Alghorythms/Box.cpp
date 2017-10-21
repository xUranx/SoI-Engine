#include "Box.h"

using namespace entityCat;

Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 position, Engine::GLTexture text, Engine::ColourRGBA8& color, const glm::vec2& dimensions)
{
	texture = text;
	colour = color;
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
	fDef.filter.categoryBits = Block;
	fixture = body->CreateFixture(&fDef);
	body->SetUserData(this);
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

void Box::draw(Engine::SpriteBatch& sBatch)
{
	glm::vec4 destRect;
	destRect.x = body->GetPosition().x - dimens.x / 2.0f;
	destRect.y = body->GetPosition().y - dimens.y / 2.0f;
	destRect.z = dimens.x;
	destRect.w = dimens.y;
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, colour, body->GetAngle());
}