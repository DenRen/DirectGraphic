#pragma once

#include "Widget.h"

enum class BUTTONSTATE
{
	WAIT, FOCUSED, PRESSED
};

class Button
{
public:
	Button (Widget *widget);

	void SetStateWait ();
	void SetStateFocused ();
	void SetStatePressed ();
	void SetStateDoubleClick ();

	void RemStateFocused ();
	void RemStatePressed ();

	virtual void Update ();
	virtual void HandleNews (News news);
	virtual BUTTONSTATE GetCurrentState ();

	virtual bool IsPressed ();
	virtual bool IsClicked ();
	virtual bool IsDoubleClicked ();

private:
	bool m_focused = false;
	bool m_pressed = false;
	bool m_prevPressed = false;
	bool m_doubleClick = false;

	Widget *m_widget;
};