#include "WinMgr.h"

WinMgr::WinMgr (WinCoor coorParent) :
	m_coor (coorParent)
{}

WinMgr::WinMgr (float parentCoorX, float parentCoorY) :
	m_coor (parentCoorX, parentCoorY)
{}

WinMgr::~WinMgr ()
{
	int size = m_childWidgets.size ();
	while (size--)
	{
		delete m_childWidgets[size];
	}
}

void WinMgr::Draw ()
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

void WinMgr::Update ()
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

void WinMgr::HandleNews (News news)
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

void WinMgr::AddChildWidget (Widget *childWidget)
{
	m_childWidgets.push_back (childWidget);
}

void WinMgr::DeleteAllChilds ()
{
	int size = m_childWidgets.size ();
	while (size--)
	{
		delete m_childWidgets[size];
	}
}

WinMgr &WinMgr::operator+=(Widget *childWidget)
{
	AddChildWidget (childWidget);
	
	return *this;
}

void WinMgr::AddWinMgrCoor (float &coorX, float &coorY)
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