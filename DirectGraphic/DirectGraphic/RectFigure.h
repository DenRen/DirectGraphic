#pragma once

struct RectFigure
{
	RectFigure ();
	RectFigure (float coorX, float coorY, float width, float height);

	bool IsContain (float coorX, float coorY) const;

	void ScaleUp (float scaleX, float scaleY);
	void Move (float deltaX, float deltaY);

	void Transpose ();

	float m_coorX;
	float m_coorY;
	float m_width;
	float m_height;
};

