#include "SpriteBatch.h"
#include <algorithm>
namespace Engine {

	SpriteBatch::SpriteBatch()
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		createVertxArray();
	}

	void SpriteBatch::begin(GlyphSortType type /*GlyphSortType::TEXTURE*/)
	{
		sortType = type;
		rBatch.clear();
		glyphs.clear();
	}

	void SpriteBatch::end()
	{
		sortGLyph();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const Colour & colour)
	{
		Glyhp* newGlyhp = new Glyhp;
		newGlyhp->texture = texture;
		newGlyhp->depth = depth;
	
		newGlyhp->topLeft.colour = colour;
		newGlyhp->topLeft.setPos(destRect.x, destRect.y + destRect.w);
		newGlyhp->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyhp->bottomLeft.colour = colour;
		newGlyhp->bottomLeft.setPos(destRect.x, destRect.y);
		newGlyhp->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyhp->bottomRight.colour = colour;
		newGlyhp->bottomRight.setPos(destRect.x + destRect.z, destRect.y);
		newGlyhp->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyhp->topRight.colour = colour;
		newGlyhp->topRight.setPos(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyhp->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		glyphs.push_back(newGlyhp);

	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(vao);
		for (int i = 0; i < rBatch.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, rBatch[i].texture);

			glDrawArrays(GL_TRIANGLES, rBatch[i].offset, rBatch[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(glyphs.size() * 6);
		if (glyphs.empty())
		{
			return;
		}
		int offset = 0;
		int cv = 0;
		rBatch.emplace_back(0, 6, glyphs[0]->texture);
		vertices[cv++] = glyphs[0]->topLeft;
		vertices[cv++] = glyphs[0]->bottomLeft;
		vertices[cv++] = glyphs[0]->bottomRight;
		vertices[cv++] = glyphs[0]->bottomRight;
		vertices[cv++] = glyphs[0]->topRight;
		vertices[cv++] = glyphs[0]->topLeft;
		offset += 6;
		for (int cg = 1; cg < glyphs.size(); cg++)
		{
			if (glyphs[cg]->texture != glyphs[cg - 1]->texture)
			{
				rBatch.emplace_back(offset, 6, glyphs[cg]->texture);
			}
			else
			{
				rBatch.back().numVertices += 6;
			}
			vertices[cv++] = glyphs[cg]->topLeft;
			vertices[cv++] = glyphs[cg]->bottomLeft;
			vertices[cv++] = glyphs[cg]->bottomRight;
			vertices[cv++] = glyphs[cg]->bottomRight;
			vertices[cv++] = glyphs[cg]->topRight;
			vertices[cv++] = glyphs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//private
	void SpriteBatch::createVertxArray()
	{
		if (vao == 0)
		{
			glGenVertexArrays(1, &vao);
		}

		glBindVertexArray(vao);

		if (vbo == 0)
		{
			glGenBuffers(1, &vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);

		glEnableVertexAttribArray(1);

		glEnableVertexAttribArray(2);

		//Pos attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGLyph()
	{
		switch (sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(), compFrontToBack);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(), compBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), compTexture);
			break;
		default:
			break;
		}
		
	}

	bool SpriteBatch::compFrontToBack(Glyhp* a, Glyhp* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compBackToFront(Glyhp* a, Glyhp* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compTexture(Glyhp* a, Glyhp* b)
	{
		return (a->texture < b->texture);
	}
}