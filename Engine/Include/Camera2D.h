#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int m_width, int m_height);

		void update();

		//Setter
		void setPos(glm::vec2& newPos) { position = newPos; needsUpdate = true;}
		void setScale(float newScale) { m_scale = newScale; needsUpdate = true;}

		//Getter
		glm::vec2 getPos() const { return position; }
		float getScale() const { return m_scale; }
		glm::mat4 getCameraMatrix() const { return cameraMatrix; }

		glm::vec2 TranslateWorldToScreen(float posX, float posY);

		glm::vec2 TranslateWorldToScreen(glm::vec2 position);

		glm::vec2 TranslateScreenToWorld(float posX, float posY);

		glm::vec2 TranslateScreenToWorld(glm::vec2 position);


	private:
		int m_width, m_height;
		bool needsUpdate;
		float m_scale;
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;
	};
}
