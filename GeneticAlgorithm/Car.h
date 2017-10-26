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

	void init(b2World* world, float rad, float friction, Engine::ColourRGBA8 color);
	void initJoint(b2Body* aBody, glm::vec4 pos, bool on);

	b2Body* getBody() const { return body; }
	b2RevoluteJoint* getJoint() const { return joint; }
	Engine::ColourRGBA8 getColour() const { return colour; }
	float getRadius() const { return radius; }
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
	void init(b2World* world, glm::vec4 Pos, Engine::ColourRGBA8 color);

	b2Body* getBody() const { return body; }
	int getTireCount() const { return tires.size(); }
	void Tinit(Tire tire, int i) { tires[i] = tire; }
	Engine::ColourRGBA8 getColour() const { return colour; }
	glm::vec2 getDimens() const { return dimensions; }
	Tire getTire(int i) const {return tires.at(i);}
	void setTires(int i) { tires.resize(i); }

	void update();
	void draw(Engine::SpriteBatch& sBatch);
private:
	Engine::ColourRGBA8 colour;
	glm::vec2 dimensions;
	b2Body* body;
	std::vector<Tire> tires;
};

