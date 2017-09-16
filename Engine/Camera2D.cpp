#include "Camera2D.h"

namespace Engine {

	Camera2D::Camera2D(): sWidth(1024), sHeight(640), position(0.0f, 0.0f), cameraMatrix(glm::mat4(1.0f)), scale(1.0f), needsUpdate(true), orthoMatrix(glm::mat4(1.0f))
	{

	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int _sWidth, int _sHeight)
	{
		sWidth = _sWidth;
		sHeight = _sHeight;
		orthoMatrix = glm::ortho(0.0f, (float)sWidth, 0.0f, (float)sHeight);
		
	}

	void Camera2D::update()
	{
		if (needsUpdate)
		{
			glm::vec3 translate(-position.x + sWidth/2, -position.y + sHeight/2, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);
			
			glm::vec3 xscale(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), xscale)*cameraMatrix;
			needsUpdate = false;
		}
	}
}