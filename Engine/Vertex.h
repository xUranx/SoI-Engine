#pragma once
#include <glew.h>
namespace Engine {
	struct ColourRGBA8
	{
		ColourRGBA8() : r(255), g(255), b(255), a(255) {}
		ColourRGBA8(GLubyte _r,	GLubyte _g, GLubyte _b, GLubyte _a) : r(_r), g(_g), b(_b), a(_a) {}
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Position
	{
		float x;
		float y;
	};
	struct Vertex
	{
		//Position
		Position position;
		void setPos(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		//Colour
		ColourRGBA8 colour;
		void setColour(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
		{
			colour.r = _r;
			colour.g = _g;
			colour.b = _b;
			colour.a = _a;
		}

		//UV texture cord
		UV uv;

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}