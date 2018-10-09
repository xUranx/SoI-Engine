#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
#include "GLSLProgram.h"
#include <vector>
namespace Engine {
	class DebugRenderer
	{
	public:
		DebugRenderer();
		~DebugRenderer();

		void init();
		void end();
		void drawBox(const glm::vec4& destRect, const ColourRGBA8 colour, float angle);
		void drawCircle(const glm::vec2& center, const ColourRGBA8 colour, float radius);
		void drawLine(const glm::vec2& p1, const glm::vec2& p2, const ColourRGBA8 colour);
		void render(const glm::mat4& pMat, float lineWidth);
		void dispose();

		struct DebugVertex
		{
			glm::vec2 position;
			ColourRGBA8 colour;
		};

	private:
		GLSLProgram shaderProc;
		std::vector<DebugVertex> debugVertex;
		std::vector<GLuint> indices;
		GLuint vbo = 0;
		GLuint vao = 0;
		GLuint ibo = 0;
		int numElements = 0;
	};
}