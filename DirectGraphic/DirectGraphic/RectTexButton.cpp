#include "RectTexButton.h"
#include "ResourceManager.h"

TextureButton RectTexButton::def_textureButton (nullptr, nullptr, nullptr);

void RectTexButton::InitializeDefValues (const char *pathTextureWait,
										 const char *pathTextureFocus,
										 const char *pathTexturePressed)
{
	def_textureButton.m_wait	= ResMgr::GetResMgr ()->GetTexture (pathTextureWait);
	def_textureButton.m_focused = ResMgr::GetResMgr ()->GetTexture (pathTextureFocus);
	def_textureButton.m_pressed = ResMgr::GetResMgr ()->GetTexture (pathTexturePressed);
}

RectTexButton::RectTexButton (float coorX, float coorY, float width, float height,
							  const char *pathTextureWait,
							  const char *pathTextureFocus,
							  const char *pathTextureClicked) :
	RectTexButton (coorX, coorY, width, height,
				   TextureButton (ResMgr::GetResMgr ()->GetTexture (pathTextureWait),
								  ResMgr::GetResMgr ()->GetTexture (pathTextureFocus),
								  ResMgr::GetResMgr ()->GetTexture (pathTextureClicked)))
{}

RectTexButton::RectTexButton (float coorX, float coorY, float width, float height,
							  TextureButton textureButton) :
	RectTex (coorX, coorY, width, height),
	m_textureButton (textureButton)
{
	m_texture = textureButton.m_wait;
}

void RectTexButton::Draw ()
{
	if (!Widget::IsActive ()) return;

	RectTex::Draw ();
}

void RectTexButton::Update ()
{
	if (!Widget::IsActive ()) return;

	switch (Button::GetCurrentState ())
	{
	case BUTTONSTATE::WAIT:
		Sprite::SetTexture (m_textureButton.m_wait);
		break;
	case BUTTONSTATE::FOCUSED:
		Sprite::SetTexture (m_textureButton.m_focused);
		break;
	case BUTTONSTATE::PRESSED:
		Sprite::SetTexture (m_textureButton.m_pressed);
		break;
	}

	Button::Update ();
}

void RectTexButton::HandleNews (News news)
{
	if (!Widget::IsActive ()) return;

	if (news.m_idSender == (uint16_t) SENDER_NEWS::WINAPIWNDPROC)
	{
		if (news.m_news >= NEWS::MOUSEFIRST && news.m_news <= NEWS::MOUSELAST)
		{
			if (CheckContainCursor (news.m_mousePos))
			{
				Button::SetStateFocused ();

				if (news.m_news == NEWS::LBUTTONDOWN)
				{
					Button::SetStatePressed ();
				}
				else if (news.m_news == NEWS::LBUTTONDBLCLK)
				{
					Button::SetStatePressed ();
					Button::SetStateDoubleClick ();
				}
			}
			else
			{
				Button::RemStateFocused ();
			}

			if (news.m_news == NEWS::LBUTTONUP)
			{
				Button::RemStatePressed ();
			}
		}
	}
}

bool RectTexButton::CheckContainCursor (MousePosition mousePosition)
{
	return RectTex::CheckContainCursor (mousePosition.x, mousePosition.y);
}

TextureButton::TextureButton () :
	TextureButton (nullptr, nullptr, nullptr)
{}

TextureButton::TextureButton (Texture *textureWait,
							  Texture *textureFocused,
							  Texture *textureClicked) :
	m_wait (textureWait),
	m_focused (textureFocused),
	m_pressed (textureClicked)
{}