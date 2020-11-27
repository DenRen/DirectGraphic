#include "dxRectangles.h"
#include "DXManager.h"
#include "ResourceManager.h"

Texture		 *dxRectTex::defTexture	  = nullptr;
Shader		 *dxRectTex::defShader	  = nullptr;
ID3D11Buffer *dxRectTex::defCBMatrixes  = nullptr;
WVPMatrixes  *dxRectTex::defWVPMatrixes = nullptr;

dxRectTex::dxRectTex (float coorX, float coorY, float width, float height) :
	dxRectTex (coorX, coorY, width, height,
			   defTexture, defShader,
			   defCBMatrixes, defWVPMatrixes)
{}

dxRectTex::dxRectTex (float coorX, float coorY, float width, float height,
						  const char *pathTexture) :
	dxRectTex (coorX, coorY, width, height,
			   ResMgr::GetResMgr ()->GetTexture (pathTexture), defShader,
			   defCBMatrixes, defWVPMatrixes)
{}

dxRectTex::dxRectTex (float coorX, float coorY, float width, float height,
					  Texture *texture, Shader *shader,
					  ID3D11Buffer *CBMatrix, WVPMatrixes *WVPMatrixes) :
	Sprite (shader, texture, CBMatrix, WVPMatrixes)
{
	InitializeVB ();

	ScaleUp (width, height);
	Move (coorX, coorY);
}

void dxRectTex::Draw ()
{
	Sprite::Render (DXManager::GetDeviceContext ());
}

void dxRectTex::SetDefaultValue (Texture *texture, Shader *shader,
							   ID3D11Buffer *CBMatrixes, WVPMatrixes *WVPMatrixes)
{
	defTexture	   = texture;
	defShader	   = shader;
	defCBMatrixes  = CBMatrixes;
	defWVPMatrixes = WVPMatrixes;
}

void dxRectTex::ScaleUp (float scaleUpX, float scaleUpY)
{
	Sprite::ScaleUp (scaleUpX, scaleUpY, 1.0f);
}

void dxRectTex::Move (float deltaX, float deltaY)
{
	Sprite::Move (deltaX, deltaY, 0);
}

void dxRectTex::InitializeVB ()
{
	VertexPosTex vert[4] = {{XMFLOAT3 (0.0f, -1.0f, 0.0f), XMFLOAT2 (0.0f, 1.0f)},
							{XMFLOAT3 (0.0f,  0.0f, 0.0f), XMFLOAT2 (0.0f, 0.0f)},
							{XMFLOAT3 (1.0f,  0.0f, 0.0f), XMFLOAT2 (1.0f, 0.0f)},
							{XMFLOAT3 (1.0f, -1.0f, 0.0f), XMFLOAT2 (1.0f, 1.0f)}};

	char indeces[6] = {0, 1, 2,
					   0, 2, 3};

	m_vertexBuffer.Initialize (DXManager::GetDevice (), vert, 4, indeces, 6);
}