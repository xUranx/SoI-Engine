#pragma once
#include <glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();


	void init(float _x, float _y, float _width, float _height);
	void draw();
private:
	float x, y, width, height;
	GLuint vboID;

};

