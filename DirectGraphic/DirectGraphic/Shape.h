#pragma once
class Shape
{
public:

	virtual bool IsContain (float coorX, float coorY) = 0;
	virtual void Move (float deltaX, float deltaY) = 0;

};

