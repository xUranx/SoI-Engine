#pragma once
#include "GameObj.h"
#include "Box.h"
class Player: public GameObj
{
public:
	Player();
	virtual ~Player();

	void init(b2World* world, const glm::vec2 position, Engine::ColourRGBA8 color, Engine::GLTexture textu, const glm::vec2& dimensions);

	void draw(Engine::GLSpriteBatch& sBatch);

	virtual void update();

	b2Body* getBody() { return body; }

	void takeDamg(float dmg) { m_hp -= dmg; }

	void collision(b2Fixture*);
private:
	float m_hp;
	int m_id;

	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimens = glm::vec2(0.0f);
	entityCat::entityCatecory eCat = entityCat::Block;
	Engine::GLTexture texture;
	Engine::ColourRGBA8 colour;

};

  