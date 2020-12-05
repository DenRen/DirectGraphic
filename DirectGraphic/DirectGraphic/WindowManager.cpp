#include "WindowManager.h"
#include "RectTexButton.h"
#include "Config.h"
#include "InputCoorMouse.h"
#include "ScrollerHorizontal.h"
#include "ScrollerVertical.h"
#include "RectTexButtonText.h"

#include "ScrollBarMgr.h"

WindowManager::WindowManager (WinCoor coor) :
	WidgetMgr (coor),
	m_newsQueue (NewsQueue::GetNewsQueue ()),
	m_backGround (nullptr),
	m_widgetMgr (*this)
{}

WindowManager::WindowManager (float coorX, float coorY) :
	WindowManager (WinCoor{coorX, coorY})
{}

bool WindowManager::Initialize ()
{
	RectTexButton::InitializeDefValues ("Texture\\H\\WidgetWait.png",
										"Texture\\H\\WidgetFocused.png",
										"Texture\\H\\WidgetClicked.png");

	m_backGround = new RectTex (WndCnf::minX, WndCnf::maxY, WndCnf::lenX, WndCnf::lenY,
								"Texture\\Desktop.png");

	/*
	auto buttonDarkTheme = new RectTexButton (0.7, 0.7 * WndCnf::maxY, 0.1, 0.1,
											  "Texture\\WidgetDarkTheme_Wait.png",
											  "Texture\\WidgetDarkTheme_Focused.png",
											  "Texture\\WidgetDarkTheme_Clicked.png");
	WidgetMgr::AddChildWidget (buttonDarkTheme);
	*/

	// Horizontal default values --------------------------------------------------------------------------
	/*
	ScrollerHorizontal::InitDefTex_SurfaceButton	 ("Texture\\H\\WidgetWait.png",
													  "Texture\\H\\WidgetFocused.png",
													  "Texture\\H\\WidgetClicked.png");

	ScrollerHorizontal::InitDefTex_FirstButtonArrow  ("Texture\\H\\WidgetScrollerArrowLeft_Wait.png",
													  "Texture\\H\\WidgetScrollerArrowLeft_Focused.png",
													  "Texture\\H\\WidgetScrollerArrowLeft_Clicked.png");

	ScrollerHorizontal::InitDefTex_SecondButtonArrow ("Texture\\H\\WidgetScrollerArrowRight_Wait.png",
													  "Texture\\H\\WidgetScrollerArrowRight_Focused.png",
													  "Texture\\H\\WidgetScrollerArrowRight_Clicked.png");

	ScrollerHorizontal::InitDefTex_ScrollSlider		 ("Texture\\H\\WidgetScrollerSlider_Wait.png",
													  "Texture\\H\\WidgetScrollerSlider_Focused.png",
													  "Texture\\H\\WidgetScrollerSlider_Clicked.png");
	*/
	// Vertical default values ----------------------------------------------------------------------------

	ScrollerVertical::InitDefTex_SurfaceButton     ("Texture\\V\\WidgetWait.png",
												    "Texture\\V\\WidgetFocused.png",
												    "Texture\\V\\WidgetClicked.png");

	ScrollerVertical::InitDefTex_FirstButtonArrow  ("Texture\\V\\WidgetScrollerArrowLeft_Wait.png",
												    "Texture\\V\\WidgetScrollerArrowLeft_Focused.png",
												    "Texture\\V\\WidgetScrollerArrowLeft_Clicked.png");

	ScrollerVertical::InitDefTex_SecondButtonArrow ("Texture\\V\\WidgetScrollerArrowRight_Wait.png",
													"Texture\\V\\WidgetScrollerArrowRight_Focused.png",
													"Texture\\V\\WidgetScrollerArrowRight_Clicked.png");

	ScrollerVertical::InitDefTex_ScrollSlider	   ("Texture\\V\\WidgetScrollerSlider_Wait.png",
												    "Texture\\V\\WidgetScrollerSlider_Focused.png",
												    "Texture\\V\\WidgetScrollerSlider_Clicked.png");

	// -------------------------------------------------------------------------------------------------

	RectTexButtonText::InitDefFont ("Font\\font.fnt", "Font\\font_0.png");

	// -------------------------------------------------------------------------------------------------

	/*auto rect0 = new RectTex (0, 0.05, 0.4, 0.05, "Texture\\metall.dds");
	m_widgetMgr += rect0;

	auto rect = new RectTex (0, 0, 0.4, 0.1);
	m_widgetMgr += rect;

	rect->SetOrigin (0, -0.1);
	rect->ScaleUp (1, 2);*/

	

	auto scrollBarMgr = new ScrollBarMgr (-0.4, 0.4, 0.7, 0.8,
										   0.07, 0.1, 10, fs::current_path ());

	WidgetMgr::AddChildWidget (scrollBarMgr);

	//auto button = new RectTexButtonText (0.0, +0.5, 0.3, 0.05, "Hello");

	//auto scrollerV = new ScrollerVertical   ( 0.75, +0.4, 0.5, 0.1, 0.3);
	//auto scrollerH = new ScrollerHorizontal (-0.75, -0.4, 1.5, 0.1, 0.15);

	//WidgetMgr::AddChildWidget (scrollerH);
	//WidgetMgr::AddChildWidget (scrollerV);
	//WidgetMgr::AddChildWidget (button);

	return true;
}

void WindowManager::Draw ()
{
	m_backGround->Draw ();
	WidgetMgr::Draw ();
}

void WindowManager::Update ()
{
	if (InputCoorMouse::Changed ())
	{
		News newsMouseCoor ((uint16_t) SENDER_NEWS::WINAPIWNDPROC);
		newsMouseCoor.m_news = NEWS::MOUSEMOVE;
		newsMouseCoor.m_mousePos = InputCoorMouse::GetPosition ();
		WidgetMgr::HandleNews (newsMouseCoor);
	}
	
	int curSize = m_newsQueue->GetSize ();
	while (curSize--)
	{
		News news = m_newsQueue->GetNews ();
		WidgetMgr::HandleNews (news);
	}

	WidgetMgr::Update ();
}