#include "Button.h"

Button::Button (float coorX, float coorY) :
	Widget (coorX, coorY)
{}

void Button::SetStateWait ()
{
	m_focused = false;
}

void Button::SetStateFocused ()
{
	m_focused = true;
}
void Button::SetStatePressed ()
{
	m_pressed = true;
}
void Button::RemStateFocused ()
{
	m_focused = false;
}
void Button::RemStatePressed ()
{
	m_pressed = false;
}

void Button::Update ()
{
	m_prevPressed = m_pressed;
	
	if (!m_focused)
	{
		m_pressed = false;
	}
}

BUTTONSTATE Button::GetCurrentState ()
{
	if (!m_focused)
	{
		return BUTTONSTATE::WAIT;
	}
	else
	{
		if (m_pressed)
		{
			return BUTTONSTATE::PRESSED;
		}
		else
		{
			return BUTTONSTATE::FOCUSED;
		}
	}
}

bool Button::IsPressed ()
{
	return m_focused && m_pressed;
}

bool Button::IsClicked ()
{
	return m_focused && m_pressed && !m_prevPressed;
}