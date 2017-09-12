#include "Sprite.h"



Sprite::Sprite()
{
	vboID = 0;
}


Sprite::~Sprite()
{
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::init(float _x, float _y, float _width, float _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	if (vboID == 0)
	{
		glGenBuffers(1, &vboID);
	}

	float vertexData[12];

	vertexData[0] = _x + _width;
	vertexData[1] = _y + _height;

	vertexData[2] = _x;
	vertexData[3] = _y + _height;

	vertexData[4] = _x;
	vertexData[5] = _y;
	//
	vertexData[6] = _x;
	vertexData[7] = _y;

	vertexData[8] = _x + _width;
	vertexData[9] = _y;

	vertexData[10] = _x + _width;
	vertexData[11] = _y + _height;
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


