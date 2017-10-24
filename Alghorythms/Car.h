#pragma once
#include <Engine\SpriteBatch.h>
#include <Engine\GLTexture.h>
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <vector>
class Tire
{
public:
	Tire();
	~Tire();

	void init(b2World* world, bool ra);

	b2Body* getBody() const { return body; }
	b2RevoluteJoint* getJoint() const { return joint; }
	void setJoint(b2RevoluteJoint* revoJoint) { joint = revoJoint; }
	void update();

	void draw(Engine::SpriteBatch& sBatch);
private:
	b2RevoluteJoint* joint;
	b2Body* body;
	Engine::ColourRGBA8 colour;
	float radius;
	Engine::GLTexture texture;
};



class Car
{
public:
	Car();
	~Car();
	void init(b2World* world, glm::vec2 Pos);

	b2Body* getBody() const { return body; }

	void draw(Engine::SpriteBatch& sBatch);
	void update();
private:
	Engine::ColourRGBA8 colour;
	glm::vec2 dimensions;
	b2Body* body;
	std::vector<Tire> tires;
};

