#pragma once
#include "NewsQueue.h"

struct WidgetCoor
{
	float x = 0.0f;
	float y = 0.0f;

	WidgetCoor () = default;
	WidgetCoor (WidgetCoor &) = default;
	WidgetCoor (float x, float y);

	WidgetCoor &operator += (const WidgetCoor &rhs);
	WidgetCoor &operator -= (const WidgetCoor &rhs);
	WidgetCoor &operator *= (const WidgetCoor &rhs);
	WidgetCoor &operator /= (const WidgetCoor &rhs);

	WidgetCoor operator + (WidgetCoor &rhs);
	WidgetCoor operator - (WidgetCoor &rhs);
	WidgetCoor operator * (WidgetCoor &rhs);
	WidgetCoor operator / (WidgetCoor &rhs);
									
	//WidgetCoor operator + (WidgetCoor &rhs);
};

class Widget
{
public:

	Widget ();
	virtual ~Widget ();

	virtual void Draw () = 0;
	virtual void Update () = 0;
	virtual void HandleNews (News news) = 0;
	
	virtual void Activate ();
	virtual void Diactivate ();

	virtual bool IsActive ();

	int GetID ();

private:
	const int m_id;
	static int counterID;

	WidgetCoor m_coor;
	bool m_active = true;
};