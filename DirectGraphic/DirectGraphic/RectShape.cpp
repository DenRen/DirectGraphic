#include "RectShape.h"

RectShape::RectShape (float coorX, float coorY, float width, float height) :
	m_coorX (coorX),
	m_coorY (coorY),
	m_width (width),
	m_height (height)
{}

bool RectShape::IsContain (float coorX, float coorY)
{
	return coorX >= m_coorX && coorX <= m_coorX + m_width &&
		   coorY <= m_coorY && coorY >= m_coorY - m_height;
}

void RectShape::Move (float deltaX, float deltaY)
{
	m_coorX += deltaX;
	m_coorY += deltaY;
}
