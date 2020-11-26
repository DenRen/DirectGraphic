#pragma once

#include "RectShape.h"
#include "dxRectangles.h"

class RectTex : public dxRectTex, public RectShape
{
public:
	RectTex (float coorX, float coorY, float width, float height);
	RectTex (float coorX, float coorY, float width, float height,
			 const char *pathTexture);
	RectTex (float coorX, float coorY, float width, float height,
			 Texture *texture, Shader *shader,
			 ID3D11Buffer *CBMatrixes, WVPMatrixes *WVPMatrixes);

	void Move (float x, float y);
};