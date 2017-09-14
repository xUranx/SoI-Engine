#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int sWidth, int sHeight);

		void update();

		//Setter
		void setPos(glm::vec2& newPos) { position = newPos; }
		void setScale(float newScale) { scale = newScale; }

		//Getter
		glm::vec2 getPos() { return position; }
		float getScale() { return scale; }
		glm::mat4 getCameraMatrix() { return cameraMatrix; }
	private:
		int sWidth, sHeight;
		bool needsUpdate;
		float scale;
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;
	};
}
