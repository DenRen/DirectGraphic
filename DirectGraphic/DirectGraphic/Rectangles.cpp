#include "Rectangles.h"
#include "DXManager.h"
#include "ResourceManager.h"

Texture		 *RectTex::defTexture	  = nullptr;
Shader		 *RectTex::defShader	  = nullptr;
ID3D11Buffer *RectTex::defCBMatrixes  = nullptr;
WVPMatrixes  *RectTex::defWVPMatrixes = nullptr;

RectTex::RectTex (float coorX, float coorY, float width, float height) :
	dxRectTex (coorX, coorY, width, height),
	RectShape (coorX, coorY, width, height)
{}

RectTex::RectTex (float coorX, float coorY, float width, float height,
				  const char *pathTexture) :
	dxRectTex (coorX, coorY, width, height, pathTexture),
	RectShape (coorX, coorY, width, height)
{}

RectTex::RectTex (float coorX, float coorY, float width, float height,
				  Texture *texture, Shader *shader,
				  ID3D11Buffer *CBMatrix, WVPMatrixes *WVPMatrixes) :

	dxRectTex (coorX, coorY, width, height,
			   texture, shader, CBMatrix, WVPMatrixes),
	RectShape (coorX, coorY, width, height)
{}

void RectTex::Move (float deltaX, float deltaY)
{
	dxRectTex::Move (deltaX, deltaY);
	RectShape::Move (deltaX, deltaY);
}