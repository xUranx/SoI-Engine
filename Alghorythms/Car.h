#pragma once
#include <Engine\SpriteBatch.h>
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <vector>
class Tire
{
public:
	Tire();
	~Tire();

	void init(b2World* wordl, bool rand);

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

};



class Car
{
public:
	Car();
	~Car();
	void init(b2World* wordl, glm::vec2 Pos);

	b2Body* getBody() const { return body; }

	void draw(Engine::SpriteBatch& sBatch);
	void update();
private:
	Engine::ColourRGBA8 colour;
	glm::vec4 dimensions;
	b2Body* body;
	std::vector<Tire> tires;
};

