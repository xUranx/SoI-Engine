#pragma once
#include "GameObj.h"
#include "Box.h"
class Player: public GameObj
{
public:
	Player();
	~Player();

	void init(b2World* world, const glm::vec2 position, Engine::ColourRGBA8 color, Engine::GLTexture textu, const glm::vec2& dimensions);

	void draw(Engine::GLSpriteBatch& sBatch);

	virtual void update();

	const Box& getBox() const { return cBox; }

	void startContact() { contact = true; }
	void endContact() { contact = false; }

	void takeDamg(float dmg) { m_hp -= dmg; }
private:
	Box cBox;
	float m_hp;
	int m_id;
	bool contact = false;
};

  