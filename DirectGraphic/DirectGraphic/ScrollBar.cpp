#include "ScrollBar.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

ScrollBar::ScrollBar (float coorX, float coorY, float width, float height,
					  float widthScroll, float relHeightSlider, int capacity) :
	m_scroller (new ScrollerVertical (coorX, coorY, height, widthScroll, relHeightSlider)),
	WinMgr (coorX, coorY),
	m_capacity (capacity),
	m_numFirst (0),
	m_numActive (0),
	m_width (width),
	m_height (height),
	m_widthScroll (widthScroll)
{
	MYASSERT (capacity >= 0);
	MYASSERT (widthScroll <= width);

	m_backGround = new RectTex (coorX + m_widthScroll, coorY, width - m_widthScroll, height);

	WinMgr::AddChildWidget (m_scroller);
}

void ScrollBar::Draw ()
{
	m_backGround->Draw ();

	WinMgr::Draw ();

	int size = m_bar.size ();
	while (size--)
	{
		m_bar[size]->Draw ();
	}
}

void ScrollBar::HandleNews (News news)
{
	WinMgr::HandleNews (news);
	
	int size = m_bar.size ();
	while (size--)
	{
		m_bar[size]->HandleNews (news);
	}

	if (news.m_idSender != (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
		for (int i = 0; i < m_numActive; i++)
		{
			if (news.m_idSender == m_bar[i]->GetID () &&
				news.m_news == NEWS::LBUTTONDBLCLK)
			{
				std::string *nameFile = &m_names[m_numFirst + i];

				News news (GetID ());
				news.m_news = NEWS::SELECT_ITEM_BAR;
				news.m_args = (void *) nameFile;

				SENDNEWS (news);

				break;
			}
		}
	}
}

void ScrollBar::Update ()
{
	WinMgr::Update ();

	int size = m_bar.size ();
	auto temp_ = NewsQueue::GetNewsQueue ();
	while (size--)
	{
		m_bar[size]->Update ();
	}
}

void ScrollBar::Update (std::vector <std::string> names)
{
	Clear ();

	m_names = names;
	m_numFirst = 0;

	int quantity = m_names.size ();
	if (quantity > m_capacity)
		m_numActive = m_capacity;
	else
		m_numActive = quantity;

	float coorX = 0.0f, coorY = 0.0f;
	
	m_scroller->AddWinMgrCoor (coorX, coorY);
	coorX += m_widthScroll;

	float heightItem = m_height / m_capacity;
	float widthItem  = m_width  - m_widthScroll;

	for (int i = 0; i < m_numActive; i++)
	{
		auto item = new RectTexButtonText (coorX, coorY, widthItem, heightItem, names[i].c_str ());
		m_bar.push_back (item);
		coorY -= heightItem;
	}
}

void ScrollBar::Clear ()
{
	int size = m_bar.size ();
	while (size--)
	{
		delete m_bar[size];
	}

	m_bar.clear ();
	m_names.clear ();
	//m_idItemBar.clear ();
}