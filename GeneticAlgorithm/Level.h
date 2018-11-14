#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <array>
#include <list>
#include <Box2D/Box2D.h>
#include <Engine/Include/DebugRenderer.h>
#include <Engine/Include/SpriteBatch.h>
#include "poly2tri/poly2tri.h"
template <typename T>
using TwoD = std::vector<std::vector<T>>;
class hexa
{
public:
	
};
class Level
{
public:
	Level();
	~Level();
	void init(std::string _name, float _width, float _height);
	void bezier(int times);
	void debugPrintRaw();
	void genMapData(b2World* world, const glm::vec2 position, float tWidth);
	void draw(Engine::GLSpriteBatch& sBatch);
	b2Body* getBody() const { return body; }
private:
	b2Body* body;
	void genRawMapDataOld();
	void genRawMapData();
	TwoD<glm::u8> rawMapData;
	std::vector<glm::vec2> mapData;
	std::vector<glm::vec2> rMapData;
	std::list<p2t::Triangle*> map;
	std::vector<p2t::Triangle*> triangles;
	std::vector< std::vector<p2t::Point*> > polylines;
	std::string name;
	int width;
	int height;
	static bool compFrontToBack(glm::vec2 a, glm::vec2 b);
};

