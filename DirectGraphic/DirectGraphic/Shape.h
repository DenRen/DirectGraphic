#pragma once

class Shape
{
public:

	virtual void Move (float deltaX, float deltaY) = 0;
	virtual bool IsContain (float coorX, float coorY) const = 0;

	virtual void SetOrigin (float coorX, float coorY) = 0;
	virtual void GetOrigin (float &coorX, float &coorY) = 0;
};

