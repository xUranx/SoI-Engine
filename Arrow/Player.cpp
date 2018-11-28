#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::init(b2World * world, const glm::vec2 position, Engine::ColourRGBA8 color, Engine::GLTexture textu, const glm::vec2 & dimensions)
{

	texture = textu;
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
	fDef.filter.categoryBits = entityCat::Player;
	fixture = body->CreateFixture(&fDef);
	body->SetUserData(this);
	body->SetFixedRotation(true);

}

void Player::draw(Engine::GLSpriteBatch& sBatch)
{
	b2Vec2 pos = body->GetPosition();
	glm::vec4 destRect;
	destRect.x = body->GetPosition().x - dimens.x / 2.0f;
	destRect.y = body->GetPosition().y - dimens.y / 2.0f;
	destRect.z = dimens.x;
	destRect.w = dimens.y;
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 1.0f, colour);
}

void Player::update()
{
}

void Player::collision(b2Fixture* other)
{

}
