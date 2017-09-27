#pragma once
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <Engine\Vertex.h>
#include <Engine\Log.h>
class Planet
{
public:
	Planet();
	~Planet();
	void init(b2World* world, const glm::vec2 position, const float Rad);

	b2Body* getBody() const { return body; }
	b2Fixture* getFixture() const { return fixture; }
	b2Fixture* getsFixture() const { return sFixture; }
	const float getRadius() const { return radius; }
	const float getSoIRadius() const { return SoIRad; }
	void startContact() { hitCount++; }
	void endContact() {}
	int getHitCount() { return hitCount; }
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	b2Fixture* sFixture = nullptr;
	float radius = 0.0f;
	float SoIRad = 0.0f;
	bool contact = false;
	Engine::ColourRGBA8 color;
	int hitCount = 0;

	
};

