#pragma once

#include "NewsQueue.h"

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

	virtual bool IsActive () const;

	int GetID () const;

private:
	const int m_id;
	static int counterID;

	bool m_active = true;
};