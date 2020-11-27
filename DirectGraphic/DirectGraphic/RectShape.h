#pragma once

#include "Shape.h"
#include "RectFigure.h"

// Default origin: left, up

class RectShape : public Shape, public RectFigure
{
public:
	RectShape (float coorX, float coorY, float width, float height);

	RectFigure GetRectFigure () const;

	void SetOrigin (float coorX, float coorY);
	void GetOrigin (float &coorX, float &coorY);

	void SetOrigin (Coor coor);
	void GetOrigin (Coor &origin) const;

	bool IsContain (float coorX, float coorY) const;

	void ScaleUp (float scaleX, float scaleY);
	void Move (float deltaX, float deltaY);

	void Transpose ();
};