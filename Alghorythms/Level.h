#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <array>
#include <Box2D\Box2D.h>
template <typename T>
using TwoD = std::vector<std::vector<T>>;
class hexa
{
public:
	std::vector<glm::vec2> data;
	glm::u8 type = 0;
};
class Level
{
public:
	Level();
	~Level();
	void init(std::string _name, float _width, float _height);
	void debugPrintRaw();
private:
	void genMapData(b2World* world);
	void genRawMapDataOld();
	void genRawMapData();
	TwoD<glm::u8> rawMapData;
	std::vector<hexa> mapData;
	std::string name;
	int width ;
	int height;
};

