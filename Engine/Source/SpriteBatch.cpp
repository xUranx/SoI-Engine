#include "SpriteBatch.h"
#include <algorithm>
#include <math.h>
namespace Engine {


	Glyhp::Glyhp(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColourRGBA8& colour) :texture(Texture), depth(Depth)
	{
		topLeft.colour = colour;
		topLeft.setPos(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.colour = colour;
		bottomLeft.setPos(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.colour = colour;
		bottomRight.setPos(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.colour = colour;
		topRight.setPos(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	Glyhp::Glyhp(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint Texture, float Depth, const ColourRGBA8 & colour, float angle) :texture(Texture), depth(Depth)
	{
		glm::vec2 hlfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		glm::vec2 tl(-hlfDims.x, hlfDims.y);
		glm::vec2 bl(-hlfDims.x, -hlfDims.y);
		glm::vec2 br(hlfDims.x, -hlfDims.y);
		glm::vec2 tr(hlfDims.x, hlfDims.y);
		//RotatePoints
		tl = rotatePoint(tl, angle);
		bl = rotatePoint(bl, angle);
		br = rotatePoint(br, angle);
		tr = rotatePoint(tr, angle);

		tl += hlfDims;
		bl += hlfDims;
		br += hlfDims;
		tr += hlfDims;

		topLeft.colour = colour;
		topLeft.setPos(destRect.x + tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.colour = colour;
		bottomLeft.setPos(destRect.x + bl.x, destRect.y + bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.colour = colour;
		bottomRight.setPos(destRect.x + br.x, destRect.y + br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.colour = colour;
		topRight.setPos(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}

	GlyhpTri::GlyhpTri(const glm::vec2 destRect[], const glm::vec4 & uvRect, GLuint Texture, float Depth, const ColourRGBA8 & colour)
	{
		A.colour = colour;
		A.setPos(destRect[0].x, destRect[0].y);
		A.setUV(uvRect.x, uvRect.y);

		B.colour = colour;
		B.setPos(destRect[1].x, destRect[1].y);
		B.setUV(uvRect.x, uvRect.y);

		C.colour = colour;
		C.setPos(destRect[2].x, destRect[2].y);
		C.setUV(uvRect.x, uvRect.y);
	}

	GlyhpTri::GlyhpTri(const glm::vec2 destRect[], const glm::vec4 & uvRect, GLuint Texture, float Depth, const ColourRGBA8 & colour, float angle, glm::vec2 pivot)
	{

		glm::vec2 a = rotatePoint(destRect[0], angle, pivot);
		glm::vec2 b = rotatePoint(destRect[1], angle, pivot);
		glm::vec2 c = rotatePoint(destRect[2], angle, pivot);

		A.colour = colour;
		A.setPos(a.x, a.y);
		A.setUV(uvRect.x, uvRect.y);

		B.colour = colour;
		B.setPos(b.x, b.y);
		B.setUV(uvRect.x, uvRect.y);

		C.colour = colour;
		C.setPos(c.x, c.y);
		C.setUV(uvRect.x, uvRect.y);
	}

	glm::vec2 GlyhpTri::rotatePoint(glm::vec2 pos, float angle, glm::vec2 pivot)
	{
		glm::vec2 newv;
		pos -= pivot;
		newv.x = (pos.x * cos(angle) - pos.y * sin(angle)) + pivot.x;
		newv.y = (pos.x * sin(angle) + pos.y * cos(angle)) + pivot.y;
		return newv;
	}

	glm::vec2 Glyhp::rotatePoint(glm::vec2 pos, float angle)
	{
		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newv;
	}


	GLSpriteBatch::GLSpriteBatch()
	{
	}


	GLSpriteBatch::~GLSpriteBatch()
	{
	}

	void GLSpriteBatch::init()
	{
		createVertxArray();
	}

	void GLSpriteBatch::begin(GlyphSortType type /*GlyphSortType::TEXTURE*/)
	{
		m_sortType = type;
		m_rBatch.clear();
		m_glyphs.clear();
		m_glyphsTri.clear();
	}

	void GLSpriteBatch::end()
	{
		m_glyphsP.resize(m_glyphs.size());
		for (int i = 0; i < m_glyphs.size(); i++)
		{
			m_glyphsP[i] = &m_glyphs[i];
		}
		m_glyphsTriP.resize(m_glyphsTri.size());
		for (int i = 0; i < m_glyphsTri.size(); i++)
		{
			m_glyphsTriP[i] = &m_glyphsTri[i];
		}
		sortGLyph();
		sortGLyphTri();
		int s = createRenderBatches();
		//createRenderBatchesTri(s);
	}

	void GLSpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const ColourRGBA8 & colour)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, colour);
	}

	void GLSpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const ColourRGBA8 & colour, float angle)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, colour, angle);
	}

	void GLSpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const ColourRGBA8 & colour, const glm::vec2& dir)
	{
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0.0f) angle = -angle;

		m_glyphs.emplace_back(destRect, uvRect, texture, depth, colour, angle);
	}

	void GLSpriteBatch::draw(const glm::vec2 destRect[], const glm::vec4 & uvRect, GLuint texture, float depth, const ColourRGBA8 & colour)
	{
		m_glyphsTri.emplace_back(destRect, uvRect, texture, depth, colour);
	}

	void GLSpriteBatch::draw(const glm::vec2 destRect[], const glm::vec4 & uvRect, GLuint texture, float depth, const ColourRGBA8 & colour, float angle, glm::vec2 pivot)
	{
		m_glyphsTri.emplace_back(destRect, uvRect, texture, depth, colour, angle, pivot);
	}

	void GLSpriteBatch::renderBatch()
	{
#ifdef WIN32
		glBindVertexArray(vao);
#else
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);

		glEnableVertexAttribArray(1);

		glEnableVertexAttribArray(2);
		//Pos attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
#endif
		for (int i = 0; i < m_rBatch.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_rBatch[i].texture);

			glDrawArrays(GL_TRIANGLES, m_rBatch[i].offset, m_rBatch[i].numVertices);
		}
#ifdef WIN32
		glBindVertexArray(0);
#else
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif // WIN32


	}

	int GLSpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphsP.size() * 6);
		if (m_glyphsP.empty())
		{
			return 0;
		}
		int offset = 0;
		int cv = 0;
		m_rBatch.emplace_back(0, 6, m_glyphsP[0]->texture);
		vertices[cv++] = m_glyphsP[0]->topLeft;
		vertices[cv++] = m_glyphsP[0]->bottomLeft;
		vertices[cv++] = m_glyphsP[0]->bottomRight;
		vertices[cv++] = m_glyphsP[0]->bottomRight;
		vertices[cv++] = m_glyphsP[0]->topRight;
		vertices[cv++] = m_glyphsP[0]->topLeft;
		offset += 6;
		for (int cg = 1; cg < m_glyphsP.size(); cg++)
		{
			if (m_glyphsP[cg]->texture != m_glyphsP[cg - 1]->texture)
			{
				m_rBatch.emplace_back(offset, 6, m_glyphsP[cg]->texture);
			}
			else
			{
				m_rBatch.back().numVertices += 6;
			}
			vertices[cv++] = m_glyphsP[cg]->topLeft;
			vertices[cv++] = m_glyphsP[cg]->bottomLeft;
			vertices[cv++] = m_glyphsP[cg]->bottomRight;
			vertices[cv++] = m_glyphsP[cg]->bottomRight;
			vertices[cv++] = m_glyphsP[cg]->topRight;
			vertices[cv++] = m_glyphsP[cg]->topLeft;
			offset += 6;
		}

		std::vector<Vertex> verticesTri;
		verticesTri.resize(m_glyphsTriP.size() * 3);
		bool Tri = true;
		if (m_glyphsTriP.empty())
		{
			Tri = false;
		}
		else
		{
			cv = 0;
			m_rBatch.emplace_back(offset, 3, m_glyphsTriP[0]->texture);
			verticesTri[cv++] = m_glyphsTriP[0]->A;
			verticesTri[cv++] = m_glyphsTriP[0]->B;
			verticesTri[cv++] = m_glyphsTriP[0]->C;
			offset += 3;
			for (int cg = 1; cg < m_glyphsTriP.size(); cg++)
			{
				if (m_glyphsTriP[cg]->texture != m_glyphsTriP[cg - 1]->texture)
				{
					m_rBatch.emplace_back(offset, 3, m_glyphsTriP[cg]->texture);
				}
				else
				{
					m_rBatch.back().numVertices += 3;
				}
				verticesTri[cv++] = m_glyphsTriP[cg]->A;
				verticesTri[cv++] = m_glyphsTriP[cg]->B;
				verticesTri[cv++] = m_glyphsTriP[cg]->C;
				offset += 3;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex) + verticesTri.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		if (Tri)
		{
			glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), verticesTri.size() * sizeof(Vertex), verticesTri.data());
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return vertices.size();
	}

	void GLSpriteBatch::createRenderBatchesTri(int s)
	{
		std::vector<Vertex> verticesTri;
		verticesTri.resize(m_glyphsTriP.size() * 3);
		if (m_glyphsTriP.empty())
		{
			return;
		}
		int offset = 0;
		int cv = 0;
		m_rBatch.emplace_back(0, 3, m_glyphsTriP[0]->texture);
		verticesTri[cv++] = m_glyphsTriP[0]->A;
		verticesTri[cv++] = m_glyphsTriP[0]->B;
		verticesTri[cv++] = m_glyphsTriP[0]->C;
		offset += 3;
		for (int cg = 1; cg < m_glyphsTriP.size(); cg++)
		{
			if (m_glyphsTriP[cg]->texture != m_glyphsTriP[cg - 1]->texture)
			{
				m_rBatch.emplace_back(offset, 3, m_glyphsTriP[cg]->texture);
			}
			else
			{
				m_rBatch.back().numVertices += 3;
			}
			verticesTri[cv++] = m_glyphsTriP[cg]->A;
			verticesTri[cv++] = m_glyphsTriP[cg]->B;
			verticesTri[cv++] = m_glyphsTriP[cg]->C;
			offset += 3;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		if(s==0)
		{ 
			glBufferData(GL_ARRAY_BUFFER, verticesTri.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		}
		glBufferSubData(GL_ARRAY_BUFFER, s, verticesTri.size() * sizeof(Vertex), verticesTri.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//private
	void GLSpriteBatch::createVertxArray()
	{
#ifdef WIN32
		if (vao == 0)
		{
			glGenVertexArrays(1, &vao);
		}
		glBindVertexArray(vao);
#endif
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

#ifdef WIN32
		glBindVertexArray(0);
#else
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif

	}
	void GLSpriteBatch::sortGLyph()
	{
		switch (m_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphsP.begin(), m_glyphsP.end(), compFrontToBack);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphsP.begin(), m_glyphsP.end(), compBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphsP.begin(), m_glyphsP.end(), compTexture);
			break;
		default:
			break;
		}	
	}
	void GLSpriteBatch::sortGLyphTri()
	{
		switch (m_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphsTriP.begin(), m_glyphsTriP.end(), compFrontToBackTri);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphsTriP.begin(), m_glyphsTriP.end(), compBackToFrontTri);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphsTriP.begin(), m_glyphsTriP.end(), compTextureTri);
			break;
		default:
			break;
		}
	}
	bool GLSpriteBatch::compFrontToBack(Glyhp* a, Glyhp* b)
	{
		return (a->depth < b->depth);
	}

	bool GLSpriteBatch::compBackToFront(Glyhp* a, Glyhp* b)
	{
		return (a->depth > b->depth);
	}

	bool GLSpriteBatch::compTexture(Glyhp* a, Glyhp* b)
	{
		return (a->texture < b->texture);
	}

	bool GLSpriteBatch::compFrontToBackTri(GlyhpTri* a, GlyhpTri* b)
	{
		return (a->depth < b->depth);
	}

	bool GLSpriteBatch::compBackToFrontTri(GlyhpTri* a, GlyhpTri* b)
	{
		return (a->depth > b->depth);
	}

	bool GLSpriteBatch::compTextureTri(GlyhpTri* a, GlyhpTri* b)
	{
		return (a->texture < b->texture);
	}
}