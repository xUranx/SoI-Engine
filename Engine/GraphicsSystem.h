#pragma once
#include<glm\glm.hpp>
#include"Include\SpriteBatch.h"
namespace Engine
{


	enum GSystem
	{
		GLES20, GL, DX11
	};
	class GraphicsSystem
	{
	public:
		
		void init(GSystem system);

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);

		//Draw with angle
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, float angle);

		//Draw with direction
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, const glm::vec2& dir);

		void draw(const glm::vec2 destRect[], const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);

		void draw(const glm::vec2 destRect[], const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour, float angle, glm::vec2 pivot);

		//Start Draw
		void begin();

		//End Draw
		void end();

		//Render objects
		void render();

	private:
		SpriteBatch m_sBatch;
		GSystem m_system;
	};
}

