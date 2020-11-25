#include "Widget.h"
#include "NewsQueue.h"

int Widget::counterID = (int) SENDER_NEWS::SIZE;

Widget::Widget () :
	m_id (Widget::counterID++)
{}
Widget::Widget (float coorX, float coorY) :
	Widget ()
{
	SetCoor (coorX, coorY);
}
Widget::~Widget ()
{

}

void Widget::Activate ()
{
	m_active = true;
}
void Widget::Diactivate ()
{
	m_active = false;
}

bool Widget::IsActive () const
{
	return m_active;
}

void Widget::SetCoor (float x, float y)
{
	this->m_coor = WidgetCoor (x, y);
}

int Widget::GetID () const
{
	return m_id;
}

// -----------------------------------------------------------------------

WidgetCoor::WidgetCoor () :
	WidgetCoor (0, 0)
{}
WidgetCoor::WidgetCoor (float x, float y) :
	x (x),
	y (y)
{}

WidgetCoor &WidgetCoor::operator += (const WidgetCoor &rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}
WidgetCoor &WidgetCoor::operator -= (const WidgetCoor &rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}
WidgetCoor &WidgetCoor::operator *= (const WidgetCoor &rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}
WidgetCoor &WidgetCoor::operator /= (const WidgetCoor &rhs)
{
	x /= rhs.x;
	y /= rhs.y;

	return *this;
}

WidgetCoor WidgetCoor::operator + (WidgetCoor &rhs)
{
	return WidgetCoor (x + rhs.x, y + rhs.y);
}
WidgetCoor WidgetCoor::operator - (WidgetCoor &rhs)
{
	return WidgetCoor (x - rhs.x, y - rhs.y);
}
WidgetCoor WidgetCoor::operator * (WidgetCoor &rhs)
{
	return WidgetCoor (x * rhs.x, y * rhs.y);
}
WidgetCoor WidgetCoor::operator / (WidgetCoor &rhs)
{
	return WidgetCoor (x / rhs.x, y / rhs.y);
}