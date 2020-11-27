#include "RectShape.h"

RectShape::RectShape (float coorX, float coorY, float width, float height) :
	RectFigure (coorX, coorY, width, height)
{}

RectFigure RectShape::GetRectFigure () const
{
	return RectFigure (*this);
}

void RectShape::SetOrigin (float coorX, float coorY)
{
	RectFigure::SetOrigin (coorX, coorY);
}

void RectShape::GetOrigin (float &coorX, float &coorY)
{
	RectFigure::GetOrigin (coorX, coorY);
}

void RectShape::SetOrigin (Coor coor)
{
	RectFigure::SetOrigin (coor);
}

void RectShape::GetOrigin (Coor &origin) const
{
	RectFigure::GetOrigin (origin);
}

bool RectShape::IsContain (float coorX, float coorY) const
{
	return RectFigure::IsContain (coorX, coorY);
}

void RectShape::ScaleUp (float scaleX, float scaleY)
{
	RectFigure::ScaleUp (scaleX, scaleY);
}

void RectShape::Move (float deltaX, float deltaY)
{
	RectFigure::Move (deltaX, deltaY);
}

void RectShape::Transpose ()
{
	RectFigure::Transpose ();
}
