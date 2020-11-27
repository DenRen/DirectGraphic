#pragma once

#include "Shape.h"
#include "NewsQueue.h"

class Widget
{
public:

	Widget (Shape *shape);
	virtual ~Widget ();

	virtual void Draw () = 0;
	virtual void Update () = 0;
	virtual void HandleNews (News news);
	
	virtual void Activate ();
	virtual void Diactivate ();

	virtual bool IsActive () const;

	int GetID () const;

	Shape *GetShape ();

private:
	const int m_id;
	static int counterID;

	bool m_active = true;

	Shape *m_shape;	// If nullptr, that WidgetMgr

	MousePosition m_prevMousePos;
};