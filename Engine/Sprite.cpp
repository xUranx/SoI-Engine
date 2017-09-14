#include "Sprite.h"
#include "Vertex.h"
#include  <cstddef>
#include "ResourceManager.h"
namespace Engine {
	Sprite::Sprite() : vboID(0)
	{

	}


	Sprite::~Sprite()
	{
		if (vboID != 0)
		{
			glDeleteBuffers(1, &vboID);
		}
	}

	void Sprite::init(float _x, float _y, float _width, float _height, std::string texturePath)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;

		textu = ResourceManager::getTexture(texturePath);

		if (vboID == 0)
		{
			glGenBuffers(1, &vboID);
		}

		Vertex vertexData[6];

		vertexData[0].setPos(_x + _width, _y + _height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPos(_x, _y + _height);
		vertexData[1].setUV(0.0, 1.0f);

		vertexData[2].setPos(_x, _y);
		vertexData[2].setUV(0.0f, 0.0f);

		vertexData[3].setPos(_x, _y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPos(_x + _width, _y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPos(_x + _width, _y + _height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].setColour(255, 255, 255, 255);
		}
		//vertexData[1].setColour(255, 255, 0, 255);
		//vertexData[4].setColour(0, 255, 255, 255);
		//vertexData[2].setColour(0, 0, 255, 255);
		//vertexData[3].setColour(0, 0, 255, 255);



		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{

		glBindTexture(GL_TEXTURE_2D, textu.id);

		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		glEnableVertexAttribArray(0);

		//Pos attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

