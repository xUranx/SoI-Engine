#include "Level.h"
#include <random>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <Engine\Log.h>
#include <Engine\SpriteBatch.h>
#include <Engine\DebugRenderer.h>
#define ITE std::vector<glm::vec2>::iterator

using namespace Engine;

Level::Level()
{

}


Level::~Level()
{
}

void Level::init(std::string _name, float _width, float _height)
{
	width = (int)_width*2;
	height = (int)_height;
	name = _name;

	rawMapData.resize(height);
	for (int i = 0; i < height; i++)
	{
		rawMapData[i].resize(width);
	}

	genRawMapData();

}

void Level::debugPrintRaw(SpriteBatch* sBatch,DebugRenderer* dRender)
{
	
		
}

void Level::genMapData(b2World* world, const glm::vec2 pos, float tWidth)
{	
	b2Vec2* vertices = new b2Vec2[(mapData.size() * 2) + 4];
	int vpos = 0;
	int i = 0;
	for (i = 0; i < mapData.size(); i++)
	{
		vertices[vpos++].Set(mapData[i].x - tWidth/2, mapData[i].y);
	}
	vertices[vpos++].Set(0, mapData[i].y);
	vertices[vpos++].Set(0, mapData[0].y - 2);
	vertices[vpos++].Set(width, mapData[0].y - 2);
	vertices[vpos++].Set(width, mapData[i].y);
	for (i; i >= 0; i--)
	{
		vertices[vpos++].Set(mapData[i].x + tWidth / 2, mapData[i].y);
	}

	b2BodyDef bDef;
	bDef.type = b2_staticBody;
	bDef.position.Set(pos.x, pos.y);
	b2PolygonShape pShape;
	pShape.Set(vertices, (mapData.size() * 2) + 4);
	b2FixtureDef fDef;
	fDef.shape = &pShape;
	body = world->CreateBody(&bDef);
	body->CreateFixture(&fDef);
}

void Level::genRawMapDataOld()
{
	srand(time(NULL));
	for (int i = 0; i < width; i++)
	{
		if (i >= (width / 2) - 1 && i <= (width / 2) + 1)
		{
			rawMapData[0][i] = 1;
		}
		else
		{
			rawMapData[0][i] = 0;
		}
	}

	for (int i = 1; i < height; i++)
	{
		int count = 0;
		for (int j = 0; j < width; j++)
		{
			if ((j > 1 && j<width - 2)&& count < 3)
			{
				if (rawMapData[i - 1][j - 2] == 1 && (rawMapData[i][j - 2] == 0&& rawMapData[i][j - 1] == 0))
				{
					rawMapData[i][j - 1] = 1;
					count++;
				}
				if (count != 0)
				{
					rawMapData[i][j] = 1;
					count++;
				}
				else
				{
					if ((rawMapData[i - 1][j] == 1 || rawMapData[i - 1][j - 1] == 1 || rawMapData[i - 1][j + 1] == 1) && !(j<2 || j>width - 3))
					{
						int rnum = rand() % 10 + 1;
						if (rnum <= 5)
						{
							rawMapData[i][j] = 0;
						}
						else
						{
							rawMapData[i][j] = 1;
							count++;
						}
					}
					else if ((rawMapData[i - 1][j] == 1 || rawMapData[i - 1][j + 1] == 1) && j < 2)
					{
						int rnum = rand() % 10 + 1;
						if (rnum <= 5)
						{
							rawMapData[i][j] = 0;
						}
						else
						{
							rawMapData[i][j] = 1;
							count++;
						}
					}
					else if ((rawMapData[i - 1][j] == 1 || rawMapData[i - 1][j + 1] == 1) && j>width-3)
					{
						int rnum = rand() % 10 + 1;
						if (rnum <= 5)
						{
							rawMapData[i][j] = 0;
						}
						else
						{
							rawMapData[i][j] = 1;
							count++;
						}
					}
					else
					{
						rawMapData[i][j] = 0;
					}
				}
			}
			else
			{
				rawMapData[i][j] = 0;
			}
		}
	}

}




void Level::genRawMapData()
{
	//https://gamedev.stackexchange.com/questions/37887/how-do-i-generate-a-smooth-random-horizontal-2d-tunnel
	//https://www.codeproject.com/Articles/25237/Bezier-Curves-Made-Simple
	srand(time(NULL));
	int size = (height);
	
	mapData.push_back(glm::vec2(width / 2, 0));
	for (int i = 5; i < size; i+=5)
	{
		int r = rand() % width + 2;
		if (r > width - 2) r -= 2;
		mapData.push_back(glm::vec2(r,i));
	}
	bezier(4);
	Engine::Message("Raw Map Data Done");
}

bool Level::compFrontToBack(glm::vec2 a, glm::vec2 b)
{
	return (a.y < b.y);
}

void Level::bezier(int times)
{
	for (int j = 0; j < times; j++)
	{
		std::vector<glm::vec2> tempV;
		int size = mapData.size();
		int lastPos = 0;
		
		for (int i = 0; i < j+1; i++)
		{
			tempV.push_back(mapData[i]);
			lastPos = i;
		}
		int i = 0;
		for (i = j+1; i < size-j; i++)
		{
			const float y = ((mapData[lastPos].y + mapData[i].y) / 2);
			glm::vec2 temp = glm::vec2((mapData[lastPos].x + mapData[i].x) / 2, y);
			tempV.push_back(temp);			
			lastPos = i;

		}
		for (i--; i < size; i++)
		{
			tempV.push_back(mapData[i]);
		}
		mapData.clear();
		mapData = tempV;
		//std::sort(mapData.begin(), mapData.end(), compFrontToBack);
	}
}