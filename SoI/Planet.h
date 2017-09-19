#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
class Planet
{
public:
	Planet();
	~Planet();
	void init(b2World* world, const glm::vec2 position, const float Rad);

	b2Body* getBody() const { return body; }
	b2Fixture* getFixture() const { return fixture; }
	const float getRadius() const { return radius; }
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	float radius = 0.0f;
	
};

