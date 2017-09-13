#pragma once

#include <glew.h>
struct Colour
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};
struct Position
{
	float x;
	float y;
};
struct Vertex 
{
	Position position;
	
	Colour colour;
	void setColour(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
	{
		colour.r = _r;
		colour.g = _g;
		colour.b = _b;
		colour.a = _a;
	}
};