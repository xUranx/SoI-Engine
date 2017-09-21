#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <array>
class hexa
{
	hexa(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, glm::vec2 e, glm::vec2 f)
	{
		data = { a, b, c, d, e, f };
	}
private:
	std::array<glm::vec2, 6> data;
	int type = 0;
};
class Level
{
public:
	Level();
	~Level();
private:

	std::vector<hexa> mapData;
};

