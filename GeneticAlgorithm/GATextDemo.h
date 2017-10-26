#pragma once
#include <string>
#include <vector>
#include <Engine\SpriteFont.h>
#include <Engine\SpriteBatch.h>

struct Member
{
	std::string DNA;
	int fitnes;
};

struct Population
{
	void setPop(int pop)
	{
		Members = std::vector<Member>(pop);
	}
	std::vector<Member> Members;
};

class GATextDemo
{
public:
	GATextDemo();
	~GATextDemo();
	bool start();
	void run();
	void print(Engine::SpriteBatch& sBatch, Engine::SpriteFont& sFont);
	bool getSegFound() const { return SeqFound; }
private:
	Population pop;
	std::vector<Member> Parents;
	std::string DNA = "This is a string we are trying to evolve!";
	bool SeqFound;
	int mutRate = 10;
	int generation = 0;
};

