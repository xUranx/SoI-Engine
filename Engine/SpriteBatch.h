#pragma once
#include "Debug.h"
#if defined(WIN32) && !defined(_FES)
#include <glew.h>
#elif defined(__ANDROID__) || defined(_FES)
#include <GLES2/gl2.h>
#endif
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

	class Glyhp
	{
	public:
		Glyhp() {};
		Glyhp(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColourRGBA8& colour);
		Glyhp(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColourRGBA8& colour, float angle);
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);
	};

	class GlyhpTri
	{
	public:
		GlyhpTri() {};
		GlyhpTri(const glm::vec2 destRect[], const glm::vec4& uvRect, GLuint Texture, float Depth, const ColourRGBA8& colour);
		GlyhpTri(const glm::vec2 destRect[], const glm::vec4 & uvRect, GLuint Texture, float Depth, const ColourRGBA8 & colour, float angle, glm::vec2 pivot);
		GLuint texture;
		float depth;

		Vertex A;
		Vertex B;
		Vertex C;
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle, glm::vec2 pivot);
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

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, float angle);

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, const glm::vec2& dir);

		void draw(const glm::vec2 destRect[], const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);

		void draw(const glm::vec2 destRect[], const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, float angle, glm::vec2 pivot);

		void renderBatch();

	private:
		int createRenderBatches();
		void createRenderBatchesTri(int s);
		void createVertxArray();
		void sortGLyph();
		void sortGLyphTri();

		static bool compFrontToBack(Glyhp* a, Glyhp* b);
		static bool compBackToFront(Glyhp* a, Glyhp* b);
		static bool compTexture(Glyhp* a, Glyhp* b);
		static bool compFrontToBackTri(GlyhpTri* a, GlyhpTri* b);
		static bool compBackToFrontTri(GlyhpTri* a, GlyhpTri* b);
		static bool compTextureTri(GlyhpTri* a, GlyhpTri* b);

		GLuint vbo = 0;
		GLuint vao = 0;

		GlyphSortType sortType;

		std::vector<Glyhp*> glyphsP;
		std::vector<Glyhp> glyphs;
		std::vector<GlyhpTri*> glyphsTriP;
		std::vector<GlyhpTri> glyphsTri;
		std::vector<RenderBatch> rBatch;
	};
}

