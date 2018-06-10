#pragma once
#include "Ship.h"
#include <vector>
#include <Engine/Include/SpriteFont.h>
#include <array>
struct ShipMember
{
	Ship ship;
	int fitness;
	float prevDist;
};
typedef std::vector<float> Layer;
typedef std::vector<Layer> Connections;

struct ShipPopulation
{
	ShipMember members;
	std::vector<Layer> neurons;
	std::vector<Connections> weights;
};

struct Output
{
	bool out[3];
};

struct Inputs
{
	bool vision[3];
	void getVision(Ship ship) { for (int i = 0; i < 3; i++) vision[i] = ship.getRay(i); }
};

class GAShip
{
public:
	GAShip();
	~GAShip();
	void init(std::vector<int> layers, int members, b2World* world, glm::vec2 goal, int mutate);
	void step();
	void mutate();
	void draw(Engine::GLSpriteBatch& sBatch);
	void print(Engine::GLSpriteBatch& sBatch, Engine::SpriteFont& sFont);
private:
	glm::vec2 m_goal;
	std::vector<ShipPopulation> popu;
	float dista = 0.0f;
	int sleep = 0;
	int Generation = 0;
	int higFit = 0;
	int mutateChance = 0.0f;

};