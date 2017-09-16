#pragma once

#include <glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace Engine {

	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyhp
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint _offset, GLuint nVert, GLuint _Texture) : offset(_offset), numVertices(nVert), texture(_Texture) {}
		GLuint offset = 0;
		GLuint numVertices = 0;
		GLuint texture = 0;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType type = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Colour& colour);

		void renderBatch();

	private:
		void createRenderBatches();
		void createVertxArray();
		void sortGLyph();

		static bool compFrontToBack(Glyhp* a, Glyhp* b);
		static bool compBackToFront(Glyhp* a, Glyhp* b);
		static bool compTexture(Glyhp* a, Glyhp* b);

		GLuint vbo = 0;
		GLuint vao = 0;

		GlyphSortType sortType;

		std::vector<Glyhp*> glyphs;
		std::vector<RenderBatch> rBatch;
	};
}

