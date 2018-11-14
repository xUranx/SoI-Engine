#include "Camera2D.h"

namespace Engine {

	Camera2D::Camera2D(): m_width(1024), m_height(640), position(0.0f, 0.0f), cameraMatrix(glm::mat4(1.0f)), m_scale(1.0f), needsUpdate(true), orthoMatrix(glm::mat4(1.0f))
	{

	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int _sWidth, int _sHeight)
	{
		m_width = _sWidth;
		m_height = _sHeight;
		orthoMatrix = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height);
		
	}

	void Camera2D::update()
	{
		if (needsUpdate)
		{
			glm::vec3 translate(-position.x + m_width/2, -position.y + m_height/2, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);
			
			glm::vec3 xscale(m_scale, m_scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), xscale)*cameraMatrix;
			needsUpdate = false;
		}
	}


glm::vec2 Camera2D::TranslateWorldToScreen(float posX, float posY)
{
	bool  neg = m_scale < 0;
	float mult = 1.0f / (neg ? -m_scale : m_scale);
	float w_half = (float)m_width * 0.5f * mult;
	float h_half = (float)m_height * 0.5f * mult;

	float cam_left = position.x - w_half;
	float cam_right = position.x + w_half;
	float cam_top = position.y + h_half;
	float cam_bottom = position.y - h_half;

	float ret_x = glm::clamp(posX, cam_left, cam_right);
	float ret_y = glm::clamp(posY, cam_bottom, cam_top);

	ret_x += -cam_left;
	ret_y += -cam_top;
	ret_x = ret_x / (cam_right - cam_left) * (float)m_width;
	ret_y = ret_y / (cam_top - cam_bottom) * (float)m_height;
	ret_y *= -1;

	if (neg)
	{
		ret_x = m_width - ret_x;
		ret_y = m_height - ret_y;
	}

	return glm::vec2(ret_x, ret_y);
}

glm::vec2  Camera2D::TranslateWorldToScreen(glm::vec2 position)
{
	return TranslateWorldToScreen(position.x, position.y);
}

glm::vec2 Camera2D::TranslateScreenToWorld(float posX, float posY)
{
	posX = glm::clamp(posX, 0.f, (float)m_width);
	posY = glm::clamp(posY, 0.f, (float)m_height);
	float w_half = (float)m_width * 0.5f;
	float h_half = (float)m_height * 0.5f;

	float mult = 1.0f / m_scale;
	float ret_x = (float)(posX - w_half + position.x * m_scale) * mult;
	float ret_y = (float)(posY - h_half - position.y * m_scale) * mult;
	ret_y *= -1;

	return glm::vec2(ret_x, ret_y);
}

glm::vec2 Camera2D::TranslateScreenToWorld(glm::vec2 position)
{
	return TranslateScreenToWorld(position.x, position.y);
}

}// namespace re
