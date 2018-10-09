#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::init(b2World * world, const glm::vec2 position, Engine::ColourRGBA8 color, Engine::GLTexture textu, const glm::vec2 & dimensions)
{
	cBox.init(world, position,textu, color, dimensions);
	b2Filter filt;
	filt.categoryBits = entityCat::Player;
	cBox.getFixture()->SetFilterData(filt);
	cBox.getBody()->SetFixedRotation(true);

}

void Player::draw(Engine::GLSpriteBatch& sBatch)
{
	cBox.draw(sBatch);
}

void Player::update()
{
}
