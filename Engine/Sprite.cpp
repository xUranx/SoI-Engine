#include "Sprite.h"
#include "Vertex.h"
#include  <cstddef>


Sprite::Sprite(): vboID(0)
{
	
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

	Vertex vertexData[6];

	vertexData[0].position.x = _x + _width;
	vertexData[0].position.y = _y + _height;

	vertexData[1].position.x = _x;
	vertexData[1].position.y = _y + _height;

	vertexData[2].position.x = _x;
	vertexData[2].position.y = _y;
	//
	vertexData[3].position.x = _x;
	vertexData[3].position.y = _y;

	vertexData[4].position.x = _x + _width;
	vertexData[4].position.y = _y;

	vertexData[5].position.x = _x + _width;
	vertexData[5].position.y = _y + _height;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].colour.r = 255;
		vertexData[i].colour.g = 200;
		vertexData[i].colour.b = 0;
		vertexData[i].colour.a = 255;
	}
	vertexData[1].colour.r = 0;
	vertexData[1].colour.g = 200;
	vertexData[1].colour.b = 0;
	vertexData[2].colour.r = 0;
	vertexData[2].colour.g = 0;
	vertexData[2].colour.b = 100;
	vertexData[3].colour.r = 0;
	vertexData[3].colour.g = 0;
	vertexData[3].colour.b = 100;
	vertexData[4].colour.r = 200;
	vertexData[4].colour.g = 100;
	vertexData[4].colour.b = 100;
	

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0);

	//Pos attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


