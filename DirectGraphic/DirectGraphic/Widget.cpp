#include "Widget.h"
#include "NewsQueue.h"
#include "InputCoorMouse.h"
#include "DebugFunc.h"

int Widget::counterID = (int) SENDER_NEWS::SIZE;

Widget::Widget (Shape *shape) :
	m_id (Widget::counterID++),
    m_shape (shape)
{}

Widget::~Widget () {}

#define ADDNEWS(msg)			    \
    case NEWS::msg:					\
    {								\
        SENDNEWS (news);		    \
    } break

void Widget::HandleNews (News news)
{
    if (m_shape == nullptr)
    {
        RETURN_THROW;
    }

	if (news.m_idSender == (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
        news.m_idSender = GetID ();

		if (news.m_news >= NEWS::MOUSEFIRST && news.m_news <= NEWS::MOUSELAST)
		{
            if (news.m_news == NEWS::MOUSEWHEEL)
            {
                if (m_shape->IsContain (m_prevMousePos.x, m_prevMousePos.y))
                {
                    news.m_mousePos = m_prevMousePos;

                    SENDNEWS (news);
                }
            }
            else
            {
                m_prevMousePos = news.m_mousePos;

                if (m_shape->IsContain (news.m_mousePos.x, news.m_mousePos.y))
                {
                    switch (news.m_news) {          // Ignore MOUSEMOVE
                        ADDNEWS (LBUTTONDOWN);
                        ADDNEWS (LBUTTONUP);
                        ADDNEWS (LBUTTONDBLCLK);
                        ADDNEWS (RBUTTONDOWN);
                        ADDNEWS (RBUTTONUP);
                        ADDNEWS (RBUTTONDBLCLK);

                        ADDNEWS (MBUTTONDOWN);
                        ADDNEWS (MBUTTONUP);
                        ADDNEWS (MBUTTONDBLCLK);

                        ADDNEWS (XBUTTONDOWN);
                        ADDNEWS (XBUTTONUP);
                        ADDNEWS (XBUTTONDBLCLK);

                        ADDNEWS (MOUSEWHEEL);
                    }
                }
            }
		}
	}
}
#undef ADDNEWS

void Widget::Activate ()
{
	m_active = true;
}
void Widget::Diactivate ()
{
	m_active = false;
}

bool Widget::IsActive () const
{
	return m_active;
}

int Widget::GetID () const
{
	return m_id;
}

Shape *Widget::GetShape ()
{
    return m_shape;
}
