#include "WidgetMgr.h"

WidgetMgr::WidgetMgr (WinCoor coorParent) :
	Widget (nullptr),
	m_coor (coorParent)
{}

WidgetMgr::WidgetMgr (float parentCoorX, float parentCoorY) :
	Widget (nullptr),
	m_coor (parentCoorX, parentCoorY)
{}

WidgetMgr::~WidgetMgr ()
{
	int size = m_childWidgets.size ();
	while (size--)
	{
		delete m_childWidgets[size];
	}
}

void WidgetMgr::Draw ()
{
	if (Widget::IsActive ())
	{
		int size = m_childWidgets.size ();
		while (size--)
		{
			auto child = m_childWidgets[size];
			if (child != nullptr)
			{
				child->Draw ();
			}
		}
	}
}

void WidgetMgr::Update ()
{
	if (Widget::IsActive ())
	{
		int size = m_childWidgets.size ();
		while (size--)
		{
			auto child = m_childWidgets[size];
			if (child != nullptr)
			{
				child->Update ();
			}
		}
	}
}

void WidgetMgr::HandleNews (News news)
{
	if (Widget::IsActive ())
	{
		int size = m_childWidgets.size ();
		while (size--)
		{
			auto child = m_childWidgets[size];
			if (child != nullptr)
			{
				child->HandleNews (news);
			}
		}
	}
}

void WidgetMgr::AddChildWidget (Widget *childWidget)
{
	m_childWidgets.push_back (childWidget);
}

void WidgetMgr::DeleteAllChilds ()
{
	int size = m_childWidgets.size ();
	while (size--)
	{
		delete m_childWidgets[size];
	}
}

WidgetMgr &WidgetMgr::operator+=(Widget *childWidget)
{
	AddChildWidget (childWidget);
	
	return *this;
}

void WidgetMgr::AddWinMgrCoor (float &coorX, float &coorY)
{
	coorX += m_coor.x;
	coorY += m_coor.y;
}

// -----------------------------------------------------------------------

WinCoor::WinCoor () :
	WinCoor (0, 0)
{}
WinCoor::WinCoor (float x, float y) :
	x (x),
	y (y)
{}

WinCoor &WinCoor::operator += (const WinCoor &rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}
WinCoor &WinCoor::operator -= (const WinCoor &rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}
WinCoor &WinCoor::operator *= (const WinCoor &rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}
WinCoor &WinCoor::operator /= (const WinCoor &rhs)
{
	x /= rhs.x;
	y /= rhs.y;

	return *this;
}

WinCoor WinCoor::operator + (WinCoor &rhs)
{
	return WinCoor (x + rhs.x, y + rhs.y);
}
WinCoor WinCoor::operator - (WinCoor &rhs)
{
	return WinCoor (x - rhs.x, y - rhs.y);
}
WinCoor WinCoor::operator * (WinCoor &rhs)
{
	return WinCoor (x * rhs.x, y * rhs.y);
}
WinCoor WinCoor::operator / (WinCoor &rhs)
{
	return WinCoor (x / rhs.x, y / rhs.y);
}