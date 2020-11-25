#pragma once

#include <vector>

#include "Widget.h"

struct WinCoor
{
	float x;
	float y;

	WinCoor ();
	WinCoor (const WinCoor &other) = default;

	WinCoor (float x, float y);

	WinCoor &operator += (const WinCoor &rhs);
	WinCoor &operator -= (const WinCoor &rhs);
	WinCoor &operator *= (const WinCoor &rhs);
	WinCoor &operator /= (const WinCoor &rhs);

	WinCoor operator + (WinCoor &rhs);
	WinCoor operator - (WinCoor &rhs);
	WinCoor operator * (WinCoor &rhs);
	WinCoor operator / (WinCoor &rhs);
};

class WinMgr : public Widget
{
public:

	WinMgr (WinCoor coorParent);
	WinMgr (float parentCoorX, float parentCoorY);
	virtual ~WinMgr ();

	virtual void Draw ();
	virtual void Update ();
	virtual void HandleNews (News news);
	
	void AddChildWidget (Widget *childWidget);
	void DeleteAllChilds ();

	WinMgr &operator += (Widget *childWidget);

	void AddWinMgrCoor (float &coorX, float &coorY);


private:
	std::vector <Widget *> m_childWidgets;

	WinCoor m_coor;
};

