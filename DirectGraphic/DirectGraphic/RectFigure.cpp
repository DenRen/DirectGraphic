#include <algorithm>

#include "RectFigure.h"

RectFigure::RectFigure () :
	RectFigure (0.0f, 0.0f, 0.0f, 0.0f)
{}

RectFigure::RectFigure (float coorX, float coorY, float width, float height) :
	m_coorX (coorX), m_coorY (coorY), m_width (width), m_height (height)
{}

bool RectFigure::IsContain (float coorX, float coorY) const
{
	return coorX >= m_coorX && coorX <= m_coorX + m_width &&
		   coorY <= m_coorY && coorY >= m_coorY - m_height;
}

void RectFigure::ScaleUp (float scaleX, float scaleY)
{
	m_coorX += m_width  * (1 - scaleX) / 2;
	m_coorY -= m_height * (1 - scaleY) / 2;
	m_width *= scaleX;
	m_height *= scaleY;
}

void RectFigure::Move (float deltaX, float deltaY)
{
	m_coorX += deltaX;
	m_coorY += deltaY;
}

void RectFigure::Transpose ()
{
	std::swap (m_coorX, m_coorY);
	std::swap (m_height, m_width);
}