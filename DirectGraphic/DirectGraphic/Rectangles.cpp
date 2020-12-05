#include "Rectangles.h"
#include "DXManager.h"
#include "ResourceManager.h"

RectTex::RectTex (float coorX, float coorY, float width, float height) :
	dxRectTex (coorX, coorY, width, height),
	RectShape (coorX, coorY, width, height),
	Widget (this)
{}

RectTex::RectTex (float coorX, float coorY, float width, float height,
				  const char *pathTexture) :
	dxRectTex (coorX, coorY, width, height, pathTexture),
	RectShape (coorX, coorY, width, height),
	Widget (this)
{}

RectTex::RectTex (float coorX, float coorY, float width, float height,
				  Texture *texture, Shader *shader,
				  ID3D11Buffer *CBMatrix, WVPMatrixes *WVPMatrixes) :

	dxRectTex (coorX, coorY, width, height,
			   texture, shader, CBMatrix, WVPMatrixes),
	RectShape (coorX, coorY, width, height),
	Widget (this)
{}

void RectTex::Move (float deltaX, float deltaY)
{
	dxRectTex::Move (deltaX, deltaY);
	RectShape::Move (deltaX, deltaY);
}

void RectTex::ScaleUp (float scaleUpX, float scaleUpY)
{
	dxRectTex::OrthoMove (-RectShape::m_origin.x, -RectShape::m_origin.y, 0.0f);		// Решить вопрос с origin
	dxRectTex::ScaleUp (scaleUpX, scaleUpY);
	dxRectTex::OrthoMove (+RectShape::m_origin.x, +RectShape::m_origin.y, 0.0f);

	RectShape::ScaleUp (scaleUpX, scaleUpY);
}

void RectTex::Draw ()
{
	dxRectTex::Draw ();
}

void RectTex::Update ()
{

}

void RectTex::HandleNews (News news)
{
	Widget::HandleNews (news);
}

