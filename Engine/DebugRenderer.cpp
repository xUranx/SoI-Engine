#include "DebugRenderer.h"
#define _USE_MATH_DEFINES
#include <math.h>

const char* VERT_SRC = R"(#version 130
	//The vertex shader operates on each vertex

	//input data from the VBO. Each vertex is 2 floats
	in vec2 vertexPosition;
in vec4 vertexColor;

out vec2 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 P;

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	//the z position is zero since we are in 2D
	gl_Position.z = 0.0;

	//Indicate that the coordinates are normalized
	gl_Position.w = 1.0;

	fragmentPosition = vertexPosition;

	fragmentColor = vertexColor;
})";

const char* FRAG_SRC = R"(#version 130
	//The fragment shader operates on each pixel in a given polygon

	in vec2 fragmentPosition;
in vec4 fragmentColor;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

void main() {

	color = fragmentColor;
})";
namespace Engine {

	DebugRenderer::DebugRenderer()
	{
	}


	DebugRenderer::~DebugRenderer()
	{
		dispose();
	}

	void DebugRenderer::init()
	{

		shaderProc.compileShadersFromSource(VERT_SRC, FRAG_SRC);
		shaderProc.addAtribute("vertexPos");
		shaderProc.addAtribute("vertexColor");
		shaderProc.linkShaders();

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ibo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void *)offsetof(DebugVertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4,GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void *)offsetof(DebugVertex, colour));
		glBindVertexArray(0);
	}

	void DebugRenderer::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, debugVertex.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, debugVertex.size() * sizeof(DebugVertex), debugVertex.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		numElements = indices.size();
		indices.clear();
		debugVertex.clear();
	}

	glm::vec2 rotatePoint(glm::vec2 pos, float angle)
	{
		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newv;
	}

	void DebugRenderer::drawBox(const glm::vec4 & destRect, const ColourRGBA8 colour, float angle)
	{
		int i = debugVertex.size();
		debugVertex.resize(debugVertex.size() + 4);

		glm::vec2 hlfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		glm::vec2 tl(-hlfDims.x, hlfDims.y);
		glm::vec2 bl(-hlfDims.x, -hlfDims.y);
		glm::vec2 br(hlfDims.x, -hlfDims.y);
		glm::vec2 tr(hlfDims.x, hlfDims.y);

		glm::vec2 posOff(destRect.x, destRect.y);

		//RotatePoints
		debugVertex[i].position = rotatePoint(tl, angle) + hlfDims + posOff;
		debugVertex[i + 1].position = rotatePoint(bl, angle) + hlfDims + posOff;
		debugVertex[i + 2].position = rotatePoint(br, angle) + hlfDims + posOff;
		debugVertex[i + 3].position = rotatePoint(tr, angle) + hlfDims + posOff;

		for (int j = i; j < i + 4; j++)
		{
			debugVertex[j].colour = colour;
		}
		indices.reserve(indices.size() + 8);

		indices.push_back(i);
		indices.push_back(i + 1);

		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 2);
		indices.push_back(i + 3);

		indices.push_back(i + 3);
		indices.push_back(i);

	}

	void DebugRenderer::drawCircle(const glm::vec2 & center, const ColourRGBA8 colour, float radius)
	{
		static const int NUM_VERTS = 100;
		int start = debugVertex.size();
		debugVertex.resize(debugVertex.size()+NUM_VERTS);
		for (int i = 0; i < NUM_VERTS; i++)
		{
			float angle = ((float)i / NUM_VERTS) * M_PI * 2.0f;
			debugVertex[start + i].position.x = cos(angle)*radius + center.x;
			debugVertex[start + i].position.y = sin(angle)*radius + center.y;
			debugVertex[start + i].colour = colour;
		}
		indices.reserve(indices.size() + NUM_VERTS * 2);
		for (int j = 0; j < NUM_VERTS - 1; j++)
		{
			indices.push_back(start + j);
			indices.push_back(start + j + 1);
		}
		indices.push_back(start + NUM_VERTS - 1);
		indices.push_back(start);
	}

	void DebugRenderer::drawLine(const glm::vec2 & p1, const glm::vec2 & p2, const ColourRGBA8 colour)
	{
		int i = debugVertex.size();
		debugVertex.resize(debugVertex.size() + 2);

		debugVertex[i].position = p1;
		debugVertex[i + 1].position = p2;

		for (int j = i; j < i + 2; j++)
		{
			debugVertex[j].colour = colour;
		}
		indices.reserve(indices.size() + 2);

		indices.push_back(i);
		indices.push_back(i + 1);
	}

	void DebugRenderer::render(const glm::mat4& pMat, float lineWidth)
	{
		shaderProc.use();

		GLint pLoc = shaderProc.getUniformLoc("P");
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, &(pMat[0][0]));
		
		glLineWidth(lineWidth);
		glBindVertexArray(vao);
		glDrawElements(GL_LINES, numElements, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shaderProc.unuse();
	}

	void DebugRenderer::dispose()
	{
		if (vao)
		{
			glDeleteVertexArrays(1, &vao);
		}
		if (vbo)
		{
			glDeleteBuffers(1, &vbo);
		}
		if (ibo)
		{
			glDeleteBuffers(1, &ibo);
		}
		shaderProc.dispose();
	}

}