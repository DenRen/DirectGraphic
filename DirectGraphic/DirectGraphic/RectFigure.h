#pragma once

struct Coor
{
	Coor ();
	Coor (float coorX, float coorY);

	Coor &operator += (const Coor &rhs);
	Coor &operator -= (const Coor &rhs);
	Coor &operator *= (const Coor &rhs);
	Coor &operator /= (const Coor &rhs);

	Coor  operator +  (const Coor &rhs);
	Coor  operator -  (const Coor &rhs);
	Coor  operator *  (const Coor &rhs);
	Coor  operator /  (const Coor &rhs);

	float x;
	float y;
};

struct RectFigure
{
	RectFigure ();
	RectFigure (float coorX, float coorY, float width, float height);

	void SetOrigin (float coorX, float coorY);
	void GetOrigin (float &coorX, float &coorY);

	void SetOrigin (Coor coor);
	void GetOrigin (Coor &origin) const;

	bool IsContain (float coorX, float coorY) const;

	void ScaleUp (float scaleX, float scaleY);
	void Move (float deltaX, float deltaY);

	void Transpose ();

	Coor m_coor;
	float m_width;
	float m_height;

	Coor m_origin;
};

