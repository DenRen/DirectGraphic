#include <cstdio>

#include "Button.h"
#include "DebugFunc.h"

Button::Button (Widget *widget) :
	m_widget (widget)
{
	if (widget == nullptr)
	{
		RETURN_THROW;
	}
}

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
	m_prevPressed = m_pressed;
	
	if (!m_focused)
	{
		m_pressed = false;
	}
}

void Button::HandleNews (News news)
{
	if (!m_widget->IsActive ()) return;

	if (news.m_idSender == (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
		if (news.m_news >= NEWS::MOUSEFIRST && news.m_news <= NEWS::MOUSELAST)
		{
			if (m_widget->GetShape ()->IsContain (news.m_mousePos.x, news.m_mousePos.y))
			{
				Button::SetStateFocused ();

				if (news.m_news == NEWS::LBUTTONDOWN)
				{
					Button::SetStatePressed ();
				}
				else if (news.m_news == NEWS::LBUTTONDBLCLK)
				{
					Button::SetStatePressed ();
					Button::SetStateDoubleClick ();
				}
			}
			else
			{
				Button::RemStateFocused ();
			}

			if (news.m_news == NEWS::LBUTTONUP)
			{
				Button::RemStatePressed ();
			}
		}
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
