#include <iostream>

#include "ScrollBar.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

ScrollBar::ScrollBar (float coorX, float coorY, float width, float height,
					  float widthScroll, float relHeightSlider, int capacity) :
	m_scroller (new ScrollerVertical (coorX, coorY, height, widthScroll, relHeightSlider)),
	WidgetMgr (coorX, coorY),
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

	WidgetMgr::AddChildWidget (m_backGround);
	WidgetMgr::AddChildWidget (m_scroller);
}

void ScrollBar::Draw ()
{
	WidgetMgr::Draw ();

	int size = m_bar.size ();
	while (size--)
	{
		m_bar[size]->Draw ();
	}
}

void ScrollBar::HandleNews (News news)
{
	WidgetMgr::HandleNews (news);
	
	int size = m_bar.size ();
	while (size--)
	{
		m_bar[size]->HandleNews (news);
	}

	if (news.m_idSender != (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
		for (int i = m_numFirst; i < m_size; i++)
		{
			if (news.m_idSender == m_bar[i]->GetID () &&
				news.m_news == NEWS::LBUTTONDBLCLK)
			{
				std::wstring *nameFile = &m_names[i];
				std::wcout << *nameFile << std::endl;

				News news (GetID ());
				news.m_news = NEWS::SELECT_ITEM_BAR;
				news.m_args = (void *) nameFile;

				SENDNEWS (news);

				break;
			}
		}
	}
}

bool IsZero (float x)
{
	const float eps = 1e-3;

	return x < eps && x > -eps;
}

void ScrollBar::Update ()
{
	WidgetMgr::Update ();

	int size = m_bar.size ();
	while (size--)
	{
		m_bar[size]->Update ();
	}

	if (m_capacity < m_size)
	{
		const float eps = 1e-3;
		float curSliderState = (1+eps)*m_scroller->GetStateSlider ();
		float deltaPositionSlider = (1+eps)*(curSliderState - m_prevSliderPosition) *
									((double) m_size - m_capacity);

		if (fabs (deltaPositionSlider) >= 1)
		{
			int numDelta = deltaPositionSlider;
			m_prevSliderPosition = curSliderState - ((double) deltaPositionSlider - numDelta) /
													((double) m_size - m_capacity);

			int size = m_bar.size ();
			RectTexButtonText *item = nullptr;

			float heightItem = m_height / m_capacity;
			float coorY = 0.0f;
			float coorParentY = 0.0f, coorParentX = 0.0f;
			WidgetMgr::AddWinMgrCoor (coorParentX, coorParentY);
			while (size--)
			{
				item = m_bar[size];

				item->Move (0.0, heightItem * numDelta);

				coorY = item->GetRectFigure ().m_coor.y;
				if (coorY > coorParentY + eps || coorParentY - m_height + heightItem > coorY + eps)
				{
					item->Diactivate ();
				}
				else
				{
					m_numFirst = size;
					item->Activate ();
				}
			}
		}
	}
}

void ScrollBar::Update (std::vector <std::wstring> names)
{
	Clear ();

	m_names = names;

	m_size = m_names.size ();
	if (m_size > m_capacity)
		m_numActive = m_capacity;
	else
		m_numActive = m_size;

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

	for (int i = m_numActive; i < m_size; i++)
	{
		auto item = new RectTexButtonText (coorX, coorY, widthItem, heightItem, names[i].c_str ());
		item->Diactivate ();
		m_bar.push_back (item);
		coorY -= heightItem;
	}
}

void ScrollBar::Clear ()
{
	m_scroller->SetSlider (0);
	int size = m_bar.size ();
	while (size--)
	{
		delete m_bar[size];
	}

	m_bar.clear ();
	m_names.clear ();

	m_numFirst = 0;
}