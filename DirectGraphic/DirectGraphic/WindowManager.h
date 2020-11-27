#pragma once
#include "WinMgr.h"
#include "Rectangles.h"

class WindowManager : public WinMgr
{
public:
	WindowManager (WinCoor coor);
	WindowManager (float coorX, float coorY);
	bool Initialize ();
	
	void Draw ();
	void Update ();
	
private:
	NewsQueue *m_newsQueue;
	RectTex *m_backGround;
};