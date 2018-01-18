#pragma once
#include "Ship.h"
#include <vector>

struct Member
{
	Ship ship;
	int fitness;
};

struct Population
{
	std::vector<Member> Members;
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
};

