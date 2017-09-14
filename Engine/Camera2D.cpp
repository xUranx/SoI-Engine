#include "Camera2D.h"

namespace Engine {

	Camera2D::Camera2D(): sWidth(1024), sHeight(640), position(0.0f, 0.0f), cameraMatrix(1.0f), scale(1.0f), needsUpdate(true), orthoMatrix(1.0f)
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
			glm::vec3 translate(-position.x, -position.y, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);
		}
	}
}