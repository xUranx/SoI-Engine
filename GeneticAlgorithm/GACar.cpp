#include "GACar.h"
#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <Engine/Include/Log.h>
#include <Engine/Include/ResourceManager.h>
GACar::GACar()
{
}


GACar::~GACar()
{
}

void GACar::init(b2World * world)
{
	int popu;
	//std::cout << "Population: "; std::cin >> popu;
	setMembers(200);

	srand(time(NULL));
	for (int i = 0; i < Members.size(); i++)
	{
		Member* memberr = new Member;
		glm::vec4 destRect;
		destRect.x = 0;
		destRect.y = -14;
		destRect.z = (float)(rand() % 80 + 20) / 10;
		destRect.w = (float)(rand() % 80 + 20) / 10;
		Engine::ColourRGBA8 color;
		color.r = (int)rand() % 255;
		color.g = (int)rand() % 255;
		color.b = (int)rand() % 255;
		color.a = 255;
		memberr->car.init(world, destRect, color);
		memberr->car.setTires(rand() % 4 + 1);
		int a = destRect.z * 10;
		int b = destRect.w * 10;
		for (int j = 0; j < memberr->car.getTireCount(); j++)
		{
			color.r = rand() % 255;
			color.g = rand() % 255;
			color.b = rand() % 255;
			color.a = 255;
			float rad = (float)(rand() % 30 + 1) / 10;
			Tire t;
			t.init(world, rad, 0.5, color);
			int radd = rad * 10;
			destRect.x = (float)(rand() % a - a / 2) / 10;
			destRect.y = (float)(rand() % b - b / 2) / 10;
			destRect.z = (float)(rand() % radd - radd/2) / 10;
			destRect.w = (float)(rand() % radd - radd/2)  / 10;
			bool on;
			if (rand() % 10 < 5)
				on = true;
			else
				on = false;
			t.initJoint(memberr->car.getBody(), destRect, on);
			memberr->car.Tinit(t ,j);
		}
		memberr->fitness = 0;
		Members[i] = memberr;
	}
}

void GACar::run(Engine::Camera2D& cam2d)
{
	
	if (ch > 60)
	{
		if (!Members[m]->car.getBody()->IsAwake())
		{
			higFit = 0;
		}
		sleep = 0;
		for (int i = 0; i < Members.size(); i++)
		{
			if (Members[i]->car.getBody()->IsAwake())
			{
				if (Members[i]->fitness + 1 < (int)Members[i]->car.getBody()->GetPosition().x)
				{
					Members[i]->fitness = (int)Members[i]->car.getBody()->GetPosition().x;
					if (Members[i]->fitness > higFit)
					{
						higFit = Members[i]->fitness;
						m = i;
					}
				}
				else if(Members[i]->car.getBody()->IsAwake())
				{
					for (int j = 0; j < Members[i]->car.getTireCount(); j++)
					{
						Members[i]->car.getTire(j).getBody()->SetAwake(false);
					}
					Members[i]->fitness = (int)Members[i]->car.getBody()->GetPosition().x;
					Members[i]->car.getBody()->SetAwake(false);

				}
				if (Members[i]->car.getBody()->GetPosition().y < -30 && Members[i]->car.getBody()->IsAwake())
				{
					for (int j = 0; j < Members[i]->car.getTireCount(); j++)
					{
						Members[i]->car.getTire(j).getBody()->SetAwake(false);
					}
					Members[i]->fitness = (int)Members[i]->car.getBody()->GetPosition().x;
					Members[i]->car.getBody()->SetAwake(false);
					
				}
			}
			else
			{
				sleep++;
			}
		}
		

		ch = 0;
	}
	
	else
	{
		ch++;
	}
	glm::vec2 ps = glm::vec2(Members[m]->car.getBody()->GetPosition().x,
							 Members[m]->car.getBody()->GetPosition().y);
	cam2d.setPos(ps);
	if (sleep >= Members.size())
	{
		//Engine::fatal_error("End");
		std::sort(Members.begin(), Members.end(),
			[](Member* a, Member* b) {return a->fitness > b->fitness; });
		/*int tF = 0;
		for (auto& b : Members)
		{
			tF += b->fitness;
		}
		int med = tF / Members.size();*/
		int memsize = Members.size();
		for (int i = 0;i < memsize; i++)
		{
			//if (med < Members[i]->fitness)
			if (i < memsize / 2)
			{
				Parent parent;
				parent.m_world = Members[i]->car.getBody()->GetWorld();
				parent.dimens = Members[i]->car.getDimens();
				parent.tirecount = Members[i]->car.getTireCount();
				parent.collours.resize(parent.tirecount + 1);
				parent.rads.resize(parent.tirecount);
				parent.joints.resize(parent.tirecount);
				parent.motor.resize(parent.tirecount);
				parent.collours[0] = Members[i]->car.getColour();
				for (int j = 0; j < parent.tirecount; j++)
					parent.collours[j + 1] = Members[i]->car.getTire(j).getColour();
				for (int j = 0; j < parent.tirecount; j++)
					parent.rads[j] = Members[i]->car.getTire(j).getRadius();
				for (int j = 0; j < parent.tirecount; j++)
				{
					parent.joints[j].x = Members[i]->car.getTire(j).getJoint()->GetLocalAnchorA().x;
					parent.joints[j].y = Members[i]->car.getTire(j).getJoint()->GetLocalAnchorA().y;
					parent.joints[j].z = Members[i]->car.getTire(j).getJoint()->GetLocalAnchorB().x;
					parent.joints[j].w = Members[i]->car.getTire(j).getJoint()->GetLocalAnchorB().y;
				}
				for (int j = 0; j < parent.tirecount; j++)
					parent.motor[j] = Members[i]->car.getTire(j).getJoint()->IsMotorEnabled();
				Parents.push_back(parent);
			}
			int tC = Members[i]->car.getTireCount();
			for (int j = 0; j < tC; j++)
			{
				Members[i]->car.getBody()->GetWorld()->DestroyBody(Members[i]->car.getTire(j).getBody());
			}

			Members[i]->car.getBody()->GetWorld()->DestroyBody(Members[i]->car.getBody());
			delete(&Members[i]->car);
			Members[i]->fitness = 0;

		}
		if (Parents.size() % 2)
			Parents.erase(Parents.end() - 1);
		srand(time(NULL));
		int pop = 0;
		int par = Parents.size();
		int k = floor(Members.size() / Parents.size());
		int r = Members.size() - Parents.size()*k;
		int mems = 0;
		for (int i = 0; i < par; i += 2)
		{

			/*int p1 = rand() % Parents.size();
			int p2 = rand() % Parents.size();
			while (p1 == p2)
			{
				p2 = rand() % Parents.size();
			}*/
			/*int a = 0;
			if (r > 0)
			{
				a = 1;
			}*/
			for (int j = 0; j < 4; j++)
			{
				int ran = rand() % 2;
				Member* memberr = new Member;
				glm::vec4 destRect;
				destRect.x = 0;
				destRect.y = -14;
				destRect.z = Parents[i + ran].dimens.x;
				destRect.w = Parents[i + ran].dimens.y;
				Engine::ColourRGBA8 color = Parents[i + ran].collours[0];

				memberr->car.init(Parents[i + ran].m_world, destRect, color);
				ran = rand() % 2;
				memberr->car.setTires(Parents[i + ran].tirecount);
				int a = destRect.z * 10;
				int b = destRect.w * 10;
				for (int l = 0; l < Parents[i + ran].tirecount; l++)
				{
					color = Parents[i + ran].collours[l + 1];
					float rad = Parents[i + ran].rads[l];
					Tire t;
					t.init(Parents[i].m_world, rad, 0.5, color);
					int radd = rad * 10;
					destRect = Parents[i + ran].joints[l];
					bool on;
					on = Parents[i + ran].motor[l];
					t.initJoint(memberr->car.getBody(), destRect, on);
					memberr->car.Tinit(t, l);
				}
				memberr->fitness = 0;
				Members[mems++] = memberr;
			}


		}
		Engine::Message("Mating Done");
		Parents.clear();
		sleep = 0;
		glm::vec2 ps = glm::vec2(Members[m]->car.getBody()->GetPosition().x,
								 Members[m]->car.getBody()->GetPosition().y);
		cam2d.setPos(ps);
		ch = -60 * 4;
		generation++;
	}
}

void GACar::draw(Engine::SpriteBatch & sBatch)
{
	for (int i = 0; i < Members.size(); i++)
	{
		Members[i]->car.draw(sBatch);
	}
}

void GACar::print(Engine::SpriteBatch& sBatch, Engine::SpriteFont& sFont)
{
#ifdef WIN32
	Engine::ColourRGBA8 colour;
	char buffer[256];

	sprintf_s(buffer, "Gen: %d Population: %d Highest Fitness: %d Sleeping: %d/%d", generation, Members.size(), higFit, sleep, Members.size());
	sFont.draw(sBatch, buffer, glm::vec2(20, 50), glm::vec2(1.0f), 0.0f, colour);
#endif
	
}
