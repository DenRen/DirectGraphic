#include "Widget.h"
#include "NewsQueue.h"

int Widget::counterID = (int) SENDER_NEWS::SIZE;

Widget::Widget () :
	m_id (Widget::counterID++)
{}
Widget::~Widget () {}

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