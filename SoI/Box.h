#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2 position, const glm::vec2& dimensions);

	b2Body* getBody() const { return body; }
	b2Fixture* getFixture() const { return fixture; }
	const glm::vec2 getDimensions() const { return dimens; }
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimens = glm::vec2(0.0f);
};

