#pragma once

#include "WidgetMgr.h"
#include "RectTexButton.h"

class Scroller : public WidgetMgr
{
public:

	Scroller (WinCoor coor, float lenght, float width, float relLengthSlider);
	Scroller (float coorX, float coorY,
			  float lenght, float width, float relLengthSlider);

	float GetDeltaPositionSlider ();
	bool SliderIsPressed ();

protected:

	float m_stateSlider;
	float m_relLengthSlider;

	bool m_startSlidering;
	float m_prevMousePosition;
	float m_deltaMousePosition;

	float m_curCoord;
	float m_startCoord;
	float m_startStateSlider;

	bool m_mousePressedAndScrolled = false;

	float m_width;
	float m_length;

	RectTexButton *m_firstButtonArrow;
	RectTexButton *m_secondButtonArrow;
	RectTexButton *m_scrollSlider;
	RectTexButton *m_firstSurfaceButton;
	RectTexButton *m_secondSurfaceButton;
};