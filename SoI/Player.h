#pragma once
#include "GameObj.h"
#include "Box.h"
class Player: public GameObj
{
public:
	Player();
	~Player();

	void init(b2World* world, const glm::vec2 position, Engine::ColourRGBA8 color, Engine::GLTexture textu, const glm::vec2& dimensions);

	void draw(Engine::SpriteBatch& sBatch);

	virtual void update();

	const Box& getBox() const { return cBox; }

private:
	Box cBox;
};

