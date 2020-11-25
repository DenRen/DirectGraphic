#pragma once
#include "Widget.h"

enum class BUTTONSTATE
{
	WAIT, FOCUSED, PRESSED
};

class Button : public Widget
{
public:

	virtual void SetStateWait ();
	virtual void SetStateFocused ();
	virtual void SetStatePressed ();
	virtual void SetStateDoubleClick ();

	virtual void RemStateFocused ();
	virtual void RemStatePressed ();

	virtual void Update ();
	virtual BUTTONSTATE GetCurrentState ();

	virtual bool IsPressed ();
	virtual bool IsClicked ();
	virtual bool IsDoubleClicked ();

private:
	bool m_focused = false;
	bool m_pressed = false;
	bool m_prevPressed = false;
	bool m_doubleClick = false;
};