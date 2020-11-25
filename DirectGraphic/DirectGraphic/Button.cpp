#include <cstdio>

#include "Button.h"

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
void Button::SetStateDoubleClick ()
{
	m_doubleClick = true;
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
	if (IsClicked ())
	{ 
		News news (GetID ());
		news.m_news = NEWS::LBUTTONCLICKED;
		news.m_args = nullptr;

		SENDNEWS (news);
	}

	if (IsDoubleClicked ())
	{
		News news (Widget::GetID ());
		news.m_news = NEWS::LBUTTONDBLCLK;
		news.m_args = nullptr;

		SENDNEWS (news);
		m_doubleClick = false;
	}

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

bool Button::IsDoubleClicked ()
{
	return m_focused && m_doubleClick;
}
