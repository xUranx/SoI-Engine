#pragma once
#include <cmath>

float SoI(float a, float m_S, float m_L)
{
	return a*(pow((m_S / m_L), (2.0 / 5.0)));
};
