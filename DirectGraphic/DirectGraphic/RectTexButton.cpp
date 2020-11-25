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
	m_textureButton (textureButton),
	Button (coorX, coorY)
{
	m_texture = textureButton.m_wait;
}

void RectTexButton::Draw ()
{
	RectTex::Draw ();
}

void RectTexButton::Update ()
{
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
	// Âîîáùå çäåñü ìîæíî ñäåëàòü îáùèé ñòàíäàðò äëÿ ëþáîé êíîïêè
	// Ïðèõîäèò news, çàïîìíèàåì íåîáõîäèìûå äàííûå è âûñòàâëÿåì ðàäíûå ôëàãè.
	// Çàòåì â Update () ýòè ôëàãè è äàííûå îáðàáàòûâàåì. Èìåííî òàì îòïðàâëÿåì íîâûå news
	// è óñòàíàâëèâàåì íîâûå òåêñòóðû, íàïðèìåð. Íî ýòî îáîáùåíèå äëÿ äëÿ îáùèõ ìåòîäîâ.

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