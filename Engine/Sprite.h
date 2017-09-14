#pragma once
#include <glew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include <string>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float _x, float _y, float _width, float _height, std::string texturePath);
	void draw();
private:
	float x, y, width, height;
	GLuint vboID;
	GLTexture textu;

};

