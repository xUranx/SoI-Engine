#define _USE_MATH_DEFINES
#include "GAShip.h"
#include <random>
#include <time.h>
#include <algorithm>
#include <math.h>
GAShip::GAShip()
{
}


GAShip::~GAShip()
{
}


void GAShip::init(std::vector<int> layers, int members, b2World* world, glm::vec2 goal, int mutate)
{	
	std::mt19937 rng(time(NULL));
	std::uniform_real_distribution<float> udist(0.0f, 1.0f);
	m_goal = goal;
	mutateChance = mutate;
	popu.resize(members);
	for (auto &c : popu)
	{
		c.neurons.resize(layers.size());
		c.weights.resize(layers.size() - 1);
		for (int i = 0; i < layers.size(); i++)
			c.neurons[i].resize(layers[i]);
		for (int i = 0; i < layers.size() - 1; i++)
		{
			c.weights[i].resize(layers[i+1]);
			for (int j = 0; j < layers[i+1]; j++)
			{
				c.weights[i][j].resize(layers[i + 1]);
				for (int k = 0; k < layers[i + 1]; k++)
				{
					c.weights[i][j][k] = udist(rng);
				}
			}

		}
		glm::vec2 dim[3];
		dim[0].x = -1.5f;
		dim[0].y = -2.0f;
		dim[1].x = 0.0f;
		dim[1].y = 2.0f;
		dim[2].x = 1.5f;
		dim[2].y = -2.0f;
		c.members.ship.init(world, glm::vec2(0), dim, false, 0.4f);
		c.members.fitness = 0;
	}
	dista = glm::length(glm::vec2(m_goal.x - popu[0].members.ship.getBody()->GetPosition().x,
								  m_goal.y - popu[0].members.ship.getBody()->GetPosition().y));
	return;
	
}

void GAShip::step()
{
	for (auto &pop : popu)
	{
		if (!pop.members.ship.getBody()->IsAwake())
			continue;
		glm::vec2 dir = glm::vec2(m_goal.x - pop.members.ship.getBody()->GetPosition().x,
								  m_goal.y - pop.members.ship.getBody()->GetPosition().y);
		float angle = pop.members.ship.getBody()->GetAngle();
		pop.neurons[0][0] = dir.x;
		pop.neurons[0][1] = dir.y;
		float dist = glm::length(dir);
		if (angle < 0)
		{
			if (-angle / 2 * M_PI > 1)
			{
				angle += (2 * M_PI)*floorf(-angle / 2.0f * M_PI);
			}
			else if (angle < 2 * M_PI)
				angle += 2 * M_PI;
		}
		else
		{
			if (angle / 2 * M_PI > 1)
			{
				angle -= (2 * M_PI)*floorf(angle / 2.0f * M_PI);
			}
			else if(angle > 2 * M_PI)
				angle -= 2 * M_PI;
		}
		pop.neurons[0][2] = angle;
		pop.neurons[0][3] = dist;
		for (int i = 0; i < pop.weights.size(); i++)
		{
			for (int j = 0; j < pop.weights[i].size(); j++)
			{
				float value = 0.15f;
				for (int k = 0; k < pop.weights[i][j].size(); k++)
				{
					value += pop.weights[i][j][k] * pop.neurons[i+1][k];
				}
				pop.neurons[i + 1][j] = tanh(value);
			}
		}

		if (pop.neurons[pop.neurons.size() - 1][0]>0.5f)
		{
			pop.members.ship.getBody()->ApplyForce(30 * pop.members.ship.getBody()->GetWorldVector(b2Vec2(0.0f , 1)), 
				pop.members.ship.getBody()->GetWorldPoint(b2Vec2(0, -1)), true);
		}
		if (pop.neurons[pop.neurons.size() - 1][1] > 0.5f && !(pop.neurons[pop.neurons.size() - 1][2]>0.5f))
		{
			pop.members.ship.getBody()->ApplyForce(25 * pop.members.ship.getBody()->GetWorldVector(b2Vec2(1.0f, 0)),
				pop.members.ship.getBody()->GetWorldPoint(b2Vec2(0, -1)), true);
		}
		if (pop.neurons[pop.neurons.size() - 1][2] > 0.5f && !(pop.neurons[pop.neurons.size() - 1][1]>0.5f))
		{
			pop.members.ship.getBody()->ApplyForce(25 * pop.members.ship.getBody()->GetWorldVector(b2Vec2(-1.0f, 0)),
				pop.members.ship.getBody()->GetWorldPoint(b2Vec2(0, -1)), true);
		}

		if (dist < 4.0f)
			pop.members.fitness += 10;
		else if (dist < 15.0f)
			pop.members.fitness += 3;
		else if(pop.members.prevDist < dist)
			pop.members.fitness++;

		if (dist > dista + 10.0f)
		{
			pop.members.ship.getBody()->SetAwake(false);
			sleep++;
		}
		pop.members.prevDist = dist;
		if (pop.members.fitness > higFit)
			higFit = pop.members.fitness;
	}
	if (popu.size() <= sleep)
	{
		mutate();
	}
	

}

void GAShip::mutate()
{
	std::mt19937 rng(time(NULL));
	
	std::uniform_int_distribution<int> udist(0, 1);
	std::uniform_real_distribution<float> radn(0.0f, 1.0f);
	std::uniform_int_distribution<int> mut(0, 1000);
	std::sort(popu.begin(), popu.end(),
		[](ShipPopulation a, ShipPopulation b) {return a.members.fitness > b.members.fitness; });
	std::vector<ShipPopulation> temp;
	for (auto& c : popu)
	{
		for (int i = 0; i < c.neurons.size(); i++)
			for (int j = 0; j < c.neurons[i].size(); j++)
				c.neurons[i][j] = 0.0f;
		c.members.ship.getBody()->SetTransform(b2Vec2(0,0), 0);
		c.members.ship.getBody()->SetAwake(true);
		c.members.fitness = 0;
		temp.push_back(c);
	}
	for (int pop = 0; pop < popu.size(); pop+=2)
	{
		for (int i = 0; i < popu[pop].weights.size(); i++)
		{
			for (int j = 0; j < popu[pop].weights[i].size(); j++)
			{
				for (int k = 0; k < popu[pop].weights[i][j].size(); k++)
				{
					if (mut(rng) < mutateChance)
						popu[pop].weights[i][j][k] = radn(rng);
					else
						popu[pop].weights[i][j][k] = temp[pop + udist(rng)].weights[i][j][k];

					if (mut(rng) < mutateChance)
						popu[pop+1].weights[i][j][k] = radn(rng);
					else						
						popu[pop+1].weights[i][j][k] = temp[pop + udist(rng)].weights[i][j][k];;
				}
			}
		}
	}
	sleep = 0;
	higFit = 0;
	Generation++;
}

void GAShip::draw(Engine::GLSpriteBatch& sBatch)
{
	for (auto c : popu)
		c.members.ship.draw(sBatch);
}
void GAShip::print(Engine::GLSpriteBatch& sBatch, Engine::SpriteFont& sFont)
{
#ifdef WIN32
	Engine::ColourRGBA8 colour;
	char buffer[256];

	sprintf_s(buffer, "Gen: %d Population: %d Highest Fitness: %d Sleeping: %d/%d", Generation, popu.size(), higFit, sleep, popu.size());
	sFont.draw(sBatch, buffer, glm::vec2(20, 50), glm::vec2(1.0f), 0.0f, colour);
#endif

}