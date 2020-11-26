#pragma once

#include "Shape.h"

// Default origin: left, up

class RectShape : public Shape
{
public:
	RectShape (float coorX, float coorY, float width, float height);
	bool IsContain (float coorX, float coorY);
	void Move (float deltaX, float deltaY);

private:
	float m_coorX;
	float m_coorY;
	float m_width;
	float m_height
};

