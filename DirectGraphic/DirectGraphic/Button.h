#pragma once
#include "Widget.h"

enum class BUTTONSTATE
{
	WAIT, FOCUSED, PRESSED
};

class Button : public Widget
{
public:

	Button (float coorX, float coorY);

	virtual void SetStateWait ();
	virtual void SetStateFocused ();
	virtual void SetStatePressed ();

	virtual void RemStateFocused ();
	virtual void RemStatePressed ();

	virtual void Update ();
	virtual BUTTONSTATE GetCurrentState ();

	virtual bool IsPressed ();
	virtual bool IsClicked ();

private:
	bool m_focused = false;
	bool m_pressed = false;

	bool m_prevPressed = false;
};