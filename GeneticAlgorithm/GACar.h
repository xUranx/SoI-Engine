#pragma once


#include <Box2D\Box2D.h>
#include "Car.h"
#include <vector>
#include <Engine\Include\SpriteFont.h>
#include <Engine\Include\Camera2D.h>




class GACar
{
public:
	GACar();
	~GACar();
	void init(b2World* world);
	void run(Engine::Camera2D& cam2d);
	void draw(Engine::SpriteBatch& sBatch);
	void print(Engine::SpriteBatch& sBatch, Engine::SpriteFont& sFont);
	bool getSegFound() const { return SeqFound; }
private:
	struct Member
	{
		Car car;
		int fitness;
	};
	struct Parent
	{
		glm::vec2 dimens;
		std::vector<glm::vec4> joints;
		std::vector<glm::vec4> collours;
	};
	int ch = -60*4;
	int higFit = 0;
	int m = 0;
	int sleep = 0;
	void setMembers(int pop) { Members.clear(); Members.resize(pop); }
	std::vector<Member*> Members;
	std::vector<Member> Parents;
	bool SeqFound;
	int mutRate = 10;
	int generation = 0;
};

