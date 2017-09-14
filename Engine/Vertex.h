#pragma once
namespace Engine {
#include <glew.h>
	struct Colour
	{
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
		Colour colour;
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