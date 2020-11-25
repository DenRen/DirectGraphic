#include "ScrollerVertical.h"
#include "ResourceManager.h"

TextureButton ScrollerVertical::def_texFirstButtonArrow;
TextureButton ScrollerVertical::def_texSecondButtonArrow;
TextureButton ScrollerVertical::def_texScrollSlider;
TextureButton ScrollerVertical::def_texSurfaceButton;

ScrollerVertical::ScrollerVertical (float coorX, float coorY, float length, float width,
									float relLengthSlider) :
	Scroller (coorX, coorY, length, width, relLengthSlider)
{

	MYASSERT (relLengthSlider <= 1.0f);

	float railLength = length - 2 * width;

	m_firstButtonArrow = new RectTexButton (coorX, coorY, width, width,
											def_texFirstButtonArrow);
	coorY -= width;

	m_secondButtonArrow = new RectTexButton (coorX, coorY - railLength, width, width,
											 def_texSecondButtonArrow);


	m_scrollSlider = new RectTexButton (coorX, coorY, width, railLength * m_relLengthSlider,
										def_texScrollSlider);

	m_firstSurfaceButton = new RectTexButton (coorX, coorY, width, railLength * m_relLengthSlider / 2,
											  def_texSurfaceButton);

	m_secondSurfaceButton = new RectTexButton (coorX, coorY - railLength * m_relLengthSlider / 2, width,
											   railLength * (1 - m_relLengthSlider / 2),
											   def_texSurfaceButton);

	WinMgr::AddChildWidget (m_scrollSlider);
	WinMgr::AddChildWidget (m_firstButtonArrow);
	WinMgr::AddChildWidget (m_secondButtonArrow);
	WinMgr::AddChildWidget (m_firstSurfaceButton);
	WinMgr::AddChildWidget (m_secondSurfaceButton);
}

void ScrollerVertical::InitDefTex_FirstButtonArrow (const char *wait, const char *focused, const char *clicked)
{
	auto mgr = ResMgr::GetResMgr ();
	def_texFirstButtonArrow.m_wait = mgr->GetTexture (wait);
	def_texFirstButtonArrow.m_focused = mgr->GetTexture (focused);
	def_texFirstButtonArrow.m_pressed = mgr->GetTexture (clicked);
}
void ScrollerVertical::InitDefTex_SecondButtonArrow (const char *wait, const char *focused, const char *clicked)
{
	auto mgr = ResMgr::GetResMgr ();
	def_texSecondButtonArrow.m_wait = mgr->GetTexture (wait);
	def_texSecondButtonArrow.m_focused = mgr->GetTexture (focused);
	def_texSecondButtonArrow.m_pressed = mgr->GetTexture (clicked);
}
void ScrollerVertical::InitDefTex_ScrollSlider (const char *wait, const char *focused, const char *clicked)
{
	auto mgr = ResMgr::GetResMgr ();
	def_texScrollSlider.m_wait = mgr->GetTexture (wait);
	def_texScrollSlider.m_focused = mgr->GetTexture (focused);
	def_texScrollSlider.m_pressed = mgr->GetTexture (clicked);
}
void ScrollerVertical::InitDefTex_SurfaceButton (const char *wait, const char *focused, const char *clicked)
{
	auto mgr = ResMgr::GetResMgr ();
	def_texSurfaceButton.m_wait = mgr->GetTexture (wait);
	def_texSurfaceButton.m_focused = mgr->GetTexture (focused);
	def_texSurfaceButton.m_pressed = mgr->GetTexture (clicked);
}

void ScrollerVertical::SetSlider (float state)
{
	const float eps = 1e-5;

	if (state <= -0.0001)
	{
		state = 0.0f;
	}
	else if (state >= 1.0001)
	{
		state = 1.0f;
	}

	//if (state <=     m_relLengthSlider / 2) state =        m_relLengthSlider / 2;
	//if (state >= 1 - m_relLengthSlider / 2) state = 1.0f - m_relLengthSlider / 2;

	float saveState = state;
	state = m_relLengthSlider / 2 + (1 - m_relLengthSlider) * state;
	float stateOld = m_relLengthSlider / 2 + (1 - m_relLengthSlider) * m_stateSlider;

	float deltaY = 0.5 * (m_length - 2 * m_width) * ((double)state - stateOld);

	m_firstSurfaceButton->ScaleUp (1.0f, state / stateOld, 1.0f);
	m_firstSurfaceButton->Move (0.0f, -deltaY, 0.0f);

	m_secondSurfaceButton->ScaleUp (1.0f, 1 / ((1.0f - stateOld) / (1.0f - state)), 1.0f);
	m_secondSurfaceButton->Move (0.0f, -deltaY, 0.0f);

	m_scrollSlider->Move (0.0f, -2 * deltaY, 0.0f);

	m_stateSlider = saveState;
}

void ScrollerVertical::MoveSlider (float deltaState)
{
	SetSlider (m_stateSlider + deltaState / ((m_length - 2 * m_width) * (1 - m_relLengthSlider)));
}

float ScrollerVertical::GetStateSlider ()
{
	return m_stateSlider;
}

void ScrollerVertical::Draw ()
{
	WinMgr::Draw ();
}

void ScrollerVertical::Update ()
{
	const float m_deltaX = 0.1;

	if (m_scrollSlider->IsPressed () || m_mousePressedAndScrolled)
	{
		m_mousePressedAndScrolled = true;
		m_scrollSlider->SetStateFocused ();
		m_scrollSlider->SetStatePressed ();

		MoveSlider (-m_deltaMousePosition);
	}
	m_deltaMousePosition = 0.0f;

	if (m_firstButtonArrow->IsClicked ())    SetSlider (m_stateSlider - m_deltaX);
	if (m_secondButtonArrow->IsClicked ())   SetSlider (m_stateSlider + m_deltaX);
	if (m_firstSurfaceButton->IsClicked ())  SetSlider (m_stateSlider - m_deltaX);
	if (m_secondSurfaceButton->IsClicked ()) SetSlider (m_stateSlider + m_deltaX);

	WinMgr::Update ();
}

void ScrollerVertical::HandleNews (News news)
{
	m_firstButtonArrow->HandleNews (news);
	m_secondButtonArrow->HandleNews (news);
	m_scrollSlider->HandleNews (news);

	if (m_scrollSlider->GetCurrentState () == BUTTONSTATE::WAIT)
	{
		m_firstSurfaceButton->HandleNews (news);
		m_secondSurfaceButton->HandleNews (news);
	}
	else
	{
		m_firstSurfaceButton->SetStateWait ();
		m_secondSurfaceButton->SetStateWait ();
	}
	
	m_deltaMousePosition = 0.0f;
	if (news.m_idSender == (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
		switch (news.m_news)
		{
		case NEWS::MOUSEMOVE:
			{
				m_deltaMousePosition = news.m_mousePos.y - m_prevMousePosition;
				m_prevMousePosition  = news.m_mousePos.y;
			} break;
		case NEWS::LBUTTONUP:
			{
				m_mousePressedAndScrolled = false;
			} break;
		}
	}
}