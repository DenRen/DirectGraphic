#include <algorithm>

#include "RectFigure.h"

RectFigure::RectFigure () :
	RectFigure (0.0f, 0.0f, 0.0f, 0.0f)
{}

RectFigure::RectFigure (float coorX, float coorY, float width, float height) :
	m_coor   (coorX, coorY), m_width (width), m_height (height),
	m_origin (coorX, coorY)
{}

void RectFigure::SetOrigin (float coorX, float coorY)
{
	m_origin.x = coorX;
	m_origin.y = coorY;
}

void RectFigure::GetOrigin (float &coorX, float &coorY)
{
	coorX = m_origin.x;
	coorY = m_origin.y;
}

void RectFigure::SetOrigin (Coor coor)
{
	m_origin = coor;
}

void RectFigure::GetOrigin (Coor &origin) const
{
	origin = m_origin;
}

bool RectFigure::IsContain (float coorX, float coorY) const
{
	return coorX >= m_coor.x && coorX <= m_coor.x + m_width &&
		   coorY <= m_coor.y && coorY >= m_coor.y - m_height;
}

void RectFigure::ScaleUp (float scaleX, float scaleY)
{
	m_coor = (m_coor - m_origin) * Coor (scaleX, scaleY) + m_origin;
	m_width  *= scaleX;
	m_height *= scaleY;
}

void RectFigure::Move (float deltaX, float deltaY)
{
	m_coor   += Coor (deltaX, deltaY);
	m_origin += Coor (deltaX, deltaY);
}

void RectFigure::Transpose ()
{
	std::swap (m_coor.x, m_coor.y);
	std::swap (m_height, m_width);
}

Coor::Coor () :
	Coor (0, 0)
{}

Coor::Coor (float coorX, float coorY) :
	x (coorX),
	y (coorY)
{}

Coor &Coor::operator += (const Coor &rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Coor &Coor::operator -= (const Coor &rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Coor &Coor::operator *= (const Coor &rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

Coor &Coor::operator /= (const Coor &rhs)
{
	x /= rhs.x;
	y /= rhs.y;

	return *this;
}

Coor Coor::operator + (const Coor &rhs)
{
	return Coor (x + rhs.x, y + rhs.y);
}

Coor Coor::operator - (const Coor &rhs)
{
	return Coor (x - rhs.x, y - rhs.y);
}

Coor Coor::operator * (const Coor &rhs)
{
	return Coor (x * rhs.x, y * rhs.y);
}

Coor Coor::operator / (const Coor &rhs)
{
	return Coor (x / rhs.x, y / rhs.y);
}
