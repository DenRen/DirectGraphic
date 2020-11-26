#pragma once

#include "RectShape.h"
#include "Sprite.h"

// Origin: left, up

class dxRectTex : public Sprite <VertexPosTex, char>
{
public:
	dxRectTex (float coorX, float coorY, float width, float height);
	dxRectTex (float coorX, float coorY, float width, float height,
			   const char *pathTexture);
	dxRectTex (float coorX, float coorY, float width, float height,
			   Texture *texture, Shader *shader,
			   ID3D11Buffer *CBMatrixes, WVPMatrixes *WVPMatrixes);

	void Draw ();
	static void SetDefaultValue (Texture *texture, Shader *shader,
								 ID3D11Buffer *CBMatrixes, WVPMatrixes *WVPMatrixes);

	void ScaleUp (float ScaleUpX, float ScaleUpY);
	void Move (float x, float y);

private:
	void InitializeVB ();

	static Texture *defTexture;
	static Shader *defShader;
	static ID3D11Buffer *defCBMatrixes;
	static WVPMatrixes *defWVPMatrixes;
};

