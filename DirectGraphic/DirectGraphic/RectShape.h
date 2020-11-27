#pragma once

#include "Shape.h"
#include "RectFigure.h"

// Default origin: left, up

class RectShape : public Shape
{
public:
	RectShape (float coorX, float coorY, float width, float height);
	bool IsContain (float coorX, float coorY) const;
	void Move (float deltaX, float deltaY);

	RectFigure GetRectFigure () const;

private:
	RectFigure m_rect;
};

