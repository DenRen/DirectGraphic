#pragma once

#include "RectTexButton.h"
#include "Text.h"

class RectTexButtonText : public RectTexButton
{
public:

	RectTexButtonText (float coorX, float coorY, float width, float height, const wchar_t *text);

	static bool InitDefFont (const char *pathFontFile, const char *pathFontTex);

	void Draw ();
	void Update ();
	void HandleNews (News news);

	void Move (float deltaX, float deltaY);

private:
	Text *m_text;

	static BitmapFont *def_font;
};