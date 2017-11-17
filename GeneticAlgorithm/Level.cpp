#include "Level.h"
#include <random>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <Engine\Include\Log.h>
#include <Engine\Include\SpriteBatch.h>
#include <Engine\Include\DebugRenderer.h>
#include <vector>
#include <list>
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

	genRawMapData();

}

void ConstrainedColor(bool constrain)
{
	if (constrain) {
		// Green
		glColor3f(0, 1, 0);
	}
	else {
		// Red
		glColor3f(1, 0, 0);
	}
}

void Level::debugPrintRaw()
{
	/*glLineWidth(2.0);
	glColor4f(1.0, 1.0, 0.0, 1.0);
	int cur = 0;
	for (int i = 1; i < mapData.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex2f((mapData[cur].x+100)*4, (mapData[cur].y+50)*4);
		glVertex2f((mapData[i].x+100)*4, (mapData[i].y+50)*4);
		cur = i;
		glEnd();
	}*/
	/*for (auto it = map.begin(); it != map.end(); it++) {
		p2t::Triangle& t = **it;
		p2t::Point& a = *t.GetPoint(0);
		p2t::Point& b = *t.GetPoint(1);
		p2t::Point& c = *t.GetPoint(2);
		ConstrainedColor(t.constrained_edge[2]);
		glBegin(GL_LINES);
		glVertex2f(a.x + 100, a.y + 100);
		glVertex2f(b.x + 100, b.y + 100);
		glEnd();

		ConstrainedColor(t.constrained_edge[0]);
		glBegin(GL_LINES);
		glVertex2f(b.x + 100, b.y + 100) ;
		glVertex2f(c.x + 100, c.y + 100);
		glEnd();

		ConstrainedColor(t.constrained_edge[1]);
		glBegin(GL_LINES);
		glVertex2f(c.x + 100, c.y + 100);
		glVertex2f(a.x + 100, a.y + 100);
		glEnd();
	}*/

	for (int i = 0; i < triangles.size(); i++) {
		p2t::Triangle& t = *triangles[i];
		p2t::Point& a = *t.GetPoint(0);
		p2t::Point& b = *t.GetPoint(1);
		p2t::Point& c = *t.GetPoint(2);

		// Red

		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(a.x * 4 + 200, a.y * 4 + 50);
		glVertex2f(b.x * 4 + 200, b.y * 4 + 50);
		glVertex2f(c.x * 4 + 200, c.y * 4 + 50);
		glEnd();
		
	}

	// green
	glColor3f(1.0, 1.0, 0.0);

	for (int i = 0; i < polylines.size(); i++) {
		std::vector<p2t::Point*> poly = polylines[i];
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < poly.size(); j++) {
			glVertex2f(poly[j]->x * 4 + 200, poly[j]->y * 4 + 50);
		}
		glEnd();
	}
}

glm::vec2 rotatePoint(glm::vec2 pos, float angle, glm::vec2 pivot)
{
	glm::vec2 newv;
	pos -= pivot;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv + pivot;
}

void Level::genMapData(b2World* world, const glm::vec2 pos, float tWidth)
{	
	if(body != nullptr) world->DestroyBody(body);
	std::vector<p2t::Point*> pLine;
	b2Vec2* vertices = new b2Vec2[(mapData.size() * 2) + 4];

	pLine.reserve((mapData.size() * 2) + 4);

	int vpos = 0;
	int i = 0;
	
	glm::vec2 pPos(mapData[i].x - tWidth / 2, mapData[i].y);

	pLine.push_back(new p2t::Point(mapData[i].x - tWidth / 2, mapData[i].y));

	b2BodyDef bDef;
	bDef.type = b2_staticBody;
	bDef.position.Set(pos.x, pos.y);
	b2EdgeShape eShape;
	b2FixtureDef fDef;
	fDef.shape = &eShape;
	body = world->CreateBody(&bDef);
	for (i = 1; i < mapData.size(); i++)
	{
		glm::vec2 pos(glm::vec2(mapData[i].x - tWidth / 2.0, mapData[i].y - tWidth / 2.0));
		pos = rotatePoint(pos, -90, mapData[i]);
		eShape.Set(b2Vec2(mapData[vpos].x - tWidth / 2.0, mapData[vpos].y), b2Vec2(mapData[i].x - tWidth / 2, mapData[i].y));
		pLine.push_back(new p2t::Point(mapData[i].x - tWidth / 2, mapData[i].y));
		/*eShape.Set(b2Vec2(pPos.x, pPos.y), b2Vec2(mapData[i].x - tWidth / 2, mapData[i].y));
		pLine.push_back(new p2t::Point(pos.x, pos.y));*/
		/*vertices[vpos++].Set(mapData[i].x - tWidth/2, mapData[i].y);*/
		vpos = i;
		pPos = pos;
		body->CreateFixture(&fDef);
	}
	i--;

	/*pLine.push_back(new p2t::Point(0, pPos.y));
	pLine.push_back(new p2t::Point(0, mapData[0].y - 2));
	pLine.push_back(new p2t::Point(width, mapData[0].y - 2));
	pLine.push_back(new p2t::Point(width, pPos.y));*/

	pLine.push_back(new p2t::Point(0, mapData[i].y));
	pLine.push_back(new p2t::Point(0, mapData[0].y - 2));
	pLine.push_back(new p2t::Point(width, mapData[0].y - 2));
	pLine.push_back(new p2t::Point(width, mapData[i].y));
	eShape.Set(b2Vec2(mapData[i].x - tWidth / 2, mapData[i].y), b2Vec2(0, mapData[i].y));
	body->CreateFixture(&fDef);

	eShape.Set(b2Vec2(0, mapData[i].y), b2Vec2(0, mapData[0].y - 2));
	body->CreateFixture(&fDef);

	eShape.Set(b2Vec2(0, mapData[0].y - 2), b2Vec2(width, mapData[0].y - 2));
	body->CreateFixture(&fDef);

	eShape.Set(b2Vec2(width, mapData[0].y), b2Vec2(width, mapData[i].y));
	body->CreateFixture(&fDef);

	eShape.Set(b2Vec2(width, mapData[i].y), b2Vec2(mapData[i].x + tWidth / 2, mapData[i].y));
	body->CreateFixture(&fDef);
	
	pLine.push_back(new p2t::Point(mapData[i].x + tWidth / 2, mapData[i].y));

	//eShape.Set(b2Vec2(pPos.x, pPos.y), b2Vec2(0, pPos.y));
	//body->CreateFixture(&fDef);

	//eShape.Set(b2Vec2(0, pPos.y), b2Vec2(0, mapData[0].y - 2));
	//body->CreateFixture(&fDef);

	//eShape.Set(b2Vec2(0, mapData[0].y - 2), b2Vec2(width, pPos.y));
	//body->CreateFixture(&fDef);
	
	//eShape.Set(b2Vec2(width, pPos.y), b2Vec2(width, pPos.y));
	//body->CreateFixture(&fDef);
	//pPos = rotatePoint(glm::vec2(mapData[i].x + tWidth / 2.0, mapData[i].y + tWidth / 2.0), 90.0f, mapData[i]);

	//eShape.Set(b2Vec2(width, pPos.y), b2Vec2(pPos.x, pPos.y));
	//body->CreateFixture(&fDef);

	//pLine.push_back(new p2t::Point(pPos.x, pPos.y));
	vpos = i;
	i--;
	for (i; i >= 0; i--)
	{
		glm::vec2 pos(glm::vec2(mapData[i].x + tWidth / 2.0, mapData[i].y + tWidth / 2.0));
		pos = rotatePoint(pos, 90, mapData[i]);
		eShape.Set(b2Vec2(mapData[vpos].x + tWidth / 2.0, mapData[vpos].y), b2Vec2(mapData[i].x + tWidth / 2, mapData[i].y));
		pLine.push_back(new p2t::Point(mapData[i].x + tWidth / 2, mapData[i].y));
		/*eShape.Set(b2Vec2(pPos.x, pPos.y), b2Vec2(pos.x, pos.y));
		pLine.push_back(new p2t::Point(pos.x, pos.y));*/
		body->CreateFixture(&fDef);
		//vertices[vpos++].Set(mapData[i].x + tWidth / 2, mapData[i].y);
		vpos = i;
		pPos = pos;
	}
	//eShape.Set(b2Vec2(pPos.x, pPos.y), b2Vec2(mapData[0].x + tWidth / 2, mapData[0].y));
	//body->CreateFixture(&fDef);
	eShape.Set(b2Vec2(mapData[0].x - tWidth / 2, mapData[0].y), b2Vec2(mapData[0].x + tWidth / 2, mapData[0].y));
	body->CreateFixture(&fDef);
	//pLine.push_back(new p2t::Point(mapData[0].x + tWidth / 2, mapData[0].y));
	polylines.push_back(pLine);

	p2t::CDT* cdt = new p2t::CDT(pLine);

	cdt->Triangulate();
	
	triangles = cdt->GetTriangles();
	
	map = cdt->GetMap();
	Engine::Message("Map Generated");

}

void Level::draw(Engine::SpriteBatch& sBatch)
{
	for (int i = 0; i < triangles.size(); i++)
	{
		Engine::ColourRGBA8 color;
		color.setColour(6.0f, 51.0f, 15.0f, 255.0f);
		glm::vec2 destRect[3];
		destRect[0].x = triangles[i]->GetPoint(0)->x;
		destRect[0].y = triangles[i]->GetPoint(0)->y;
		destRect[1].x = triangles[i]->GetPoint(1)->x;
		destRect[1].y = triangles[i]->GetPoint(1)->y;
		destRect[2].x = triangles[i]->GetPoint(2)->x;
		destRect[2].y = triangles[i]->GetPoint(2)->y;
		sBatch.draw(destRect, glm::vec4(0, 0, 0, 1), NULL, 0, color);
	}
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
	
	rMapData.push_back(glm::vec2(width / 2, 0));
	rMapData.push_back(glm::vec2(width / 2, 5));
	rMapData.push_back(glm::vec2(width / 2, 10));
	int i;
	for (i = 15; i < size; i+=1)
	{
		int r = rand() % width + 2;
		if (r > width - 5) r -= 5;
		rMapData.push_back(glm::vec2(r,i));
	}
	i += 4;
	rMapData.push_back(glm::vec2(width / 2, i));
	i += 5;
	rMapData.push_back(glm::vec2(width / 2, i));
	i += 5;
	rMapData.push_back(glm::vec2(width / 2, i));
	bezier(40);
	Engine::Message("Raw Map Data Done");
}

bool Level::compFrontToBack(glm::vec2 a, glm::vec2 b)
{
	return (a.y < b.y);
}

void Level::bezier(int times)
{
	mapData = rMapData;
	for (int j = 0; j < times; j++)
	{
		std::vector<glm::vec2> tempV;
		int size = mapData.size();
		int lastPos = 0;
		int i;
		/*for (i = 0; i < j+1; i++)
		{
			tempV.push_back(mapData[i]);
			lastPos = i;
		}*/
		tempV.push_back(mapData[0]);
		for (i = 1; i < size; i++)
		{
			const float y = ((mapData[lastPos].y + mapData[i].y) / 2);
			glm::vec2 temp = glm::vec2((mapData[lastPos].x + mapData[i].x) / 2, y);
			tempV.push_back(temp);			
			lastPos = i;

		}
		//tempV.push_back(glm::vec2(mapData[i - 1].x, mapData[i - 1].y));
		/*for (i--; i < size; i++)
		{
			tempV.push_back(mapData[i]);
		}*/
		mapData.clear();
		mapData = tempV;
		//std::sort(mapData.begin(), mapData.end(), compFrontToBack);
	}
}