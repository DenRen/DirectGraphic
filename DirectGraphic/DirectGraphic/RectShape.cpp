#include "RectShape.h"

RectShape::RectShape (float coorX, float coorY, float width, float height) :
	m_rect (coorX, coorY, width, height)
{}

bool RectShape::IsContain (float coorX, float coorY) const
{
	return m_rect.IsContain (coorX, coorY);
}

void RectShape::Move (float deltaX, float deltaY)
{
	m_rect.Move (deltaX, deltaY);
}

RectFigure RectShape::GetRectFigure () const
{
	return m_rect;
}
