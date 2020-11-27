#include <iostream>

#include "ScrollBarMgr.h"

ScrollBarMgr::ScrollBarMgr (float coorX, float coorY, float width, float height,
							float widthScroll, float relHeightSlider, int capacity,
							fs::path initPath) :
	WidgetMgr (coorX, coorY),
	m_curPath (initPath),
	m_scrollBar (new ScrollBar (coorX, coorY, width, height,
							    widthScroll, relHeightSlider, capacity))
{
	m_scrollBar->Update (GetNameFiles (initPath));
}

void ScrollBarMgr::Draw ()
{
	m_scrollBar->Draw ();
}

void ScrollBarMgr::Update ()
{
	m_scrollBar->Update ();
}

void ScrollBarMgr::HandleNews (News news)
{
	if (news.m_idSender != (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
		if (news.m_idSender == m_scrollBar->GetID ())
		{
			if (news.m_news == NEWS::SELECT_ITEM_BAR)
			{
				std::wstring nameFile = *((std::wstring *) news.m_args);
				m_curPath.append (nameFile);

				m_scrollBar->Update (GetNameFiles (m_curPath));
			}
		}
	}

	m_scrollBar->HandleNews (news);
}

std::vector <std::wstring> ScrollBarMgr::GetNameFiles (const fs::path &path)
{
	std::vector <std::wstring> files;

	fs::directory_iterator begin (path);
	fs::directory_iterator end;

	for (; begin != end; begin++)
		files.push_back (begin->path ().filename ());

	return files;
}