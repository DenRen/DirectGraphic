#include "Scroller.h"

Scroller::Scroller (WinCoor coor, float lenght, float width, float relLengthSlider) :
	m_firstButtonArrow		(nullptr),
	m_secondButtonArrow		(nullptr),
	m_scrollSlider			(nullptr),
	m_firstSurfaceButton	(nullptr),
	m_secondSurfaceButton	(nullptr),

	m_stateSlider	  (0.0f),
	m_width			  (width),
	m_length		  (lenght),
	m_relLengthSlider (relLengthSlider),
	
	m_startSlidering (false),
	m_prevMousePosition (0.0f),
	m_deltaMousePosition (0.0f),

	WidgetMgr (coor)
{}

Scroller::Scroller (float coorX, float coorY,
					float lenght, float width, float relLengthSlider) :
	Scroller (WinCoor (coorX, coorY), lenght, width, relLengthSlider)
{}

float Scroller::GetDeltaPositionSlider ()
{
	return m_scrollSlider->IsPressed () * m_deltaMousePosition;
}

bool Scroller::SliderIsPressed ()
{
	return m_scrollSlider->IsPressed ();
}