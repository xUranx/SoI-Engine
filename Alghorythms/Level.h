#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <array>
#include <Box2D\Box2D.h>
template <typename T>
using TwoD = std::vector<std::vector<T>>;
class hexa
{
	hexa(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, glm::vec2 e, glm::vec2 f)
	{
		data = { a, b, c, d, e, f };
	}
private:
	std::array<glm::vec2, 6> data;
	glm::u8 type = 0;
};
class Level
{
public:
	Level();
	~Level();
	void genMapData(b2World* w, std::string n, float _width, float _height);
private:
	TwoD<glm::u8> rawMapData;
	std::vector<hexa> mapData;
	std::string name = NULL;
	float width = 0.0f;
	float height = 0.0f;
};

