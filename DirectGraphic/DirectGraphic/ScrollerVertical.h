#pragma once
#include "Scroller.h"

class ScrollerVertical : public Scroller
{
public:

	ScrollerVertical (float coorX, float coorY, float lenght, float width,
					  float relLengthSlider);

	static void InitDefTex_FirstButtonArrow  (const char *wait, const char *focused, const char *pressed);
	static void InitDefTex_SecondButtonArrow (const char *wait, const char *focused, const char *pressed);
	static void InitDefTex_ScrollSlider      (const char *wait, const char *focused, const char *pressed);
	static void InitDefTex_SurfaceButton     (const char *wait, const char *focused, const char *pressed);

	void SetSlider (float state);
	void MoveSlider (float deltaState);	// In coord
	float GetStateSlider ();

	void Draw ();
	void Update ();
	void HandleNews (News news);

private:

	static TextureButton def_texFirstButtonArrow;
	static TextureButton def_texSecondButtonArrow;
	static TextureButton def_texScrollSlider;
	static TextureButton def_texSurfaceButton;
};