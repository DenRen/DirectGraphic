#pragma once

#include "VertexBuffer.h"
#include "Texture.h"
#include "DXManager.h"
#include "DebugFunc.h"
#include "Structure_Data.h"

template <typename VertexT, typename IndexT>
class Sprite
{
public:
	Sprite ();
	Sprite (Shader *shader, Texture *texture,
			ID3D11Buffer *CBMatrix, WVPMatrixes *WVPMatrixes);

	bool Initialize (Shader *shader, Texture *texture);

	void Render (ID3D11DeviceContext *deviceContext);	// Automaticly draw

	void Move (float x, float y, float z);
	void RotateX (float angle);
	void RotateZ (float angle);
	void RotateY (float angle);
	void ScaleUp (float ScaleUpX, float ScaleUpY, float ScaleUpZ);

	void SetTexture (Texture *texture);

protected:
	VertexBuffer <VertexT, IndexT> m_vertexBuffer;
	Texture *m_texture;
	Shader  *m_shader;

	XMMATRIX m_orthoTransform;
	XMMATRIX m_posTransform;
	WVPMatrixes *m_WVPMatrixes;
	ID3D11Buffer *m_CBWVPMatrixes;

private:
	void SetCBMatrix ();
};

template <typename VertexT, typename IndexT>
inline Sprite <VertexT, IndexT>::Sprite () :
	Sprite (nullptr, nullptr, nullptr, nullptr, XMMatrixIdentity ())
{}

template <typename VertexT, typename IndexT>
inline Sprite <VertexT, IndexT>::Sprite (Shader *shader, Texture *texture,
										 ID3D11Buffer *CBWVPMatrix, WVPMatrixes *WVPMatrixes) :
	m_shader (shader),
	m_texture (texture),
	m_CBWVPMatrixes (CBWVPMatrix),
	m_WVPMatrixes (WVPMatrixes),
	m_orthoTransform (XMMatrixIdentity ()),
	m_posTransform (XMMatrixIdentity ())
{
	/*
	if (m_shader		== nullptr || m_texture		== nullptr ||
		m_CBWVPMatrixes == nullptr || m_WVPMatrixes == nullptr)
	{
		RETURN_THROW;
	}
	*/
}

template <typename VertexT, typename IndexT>
bool Sprite <VertexT, IndexT>::Initialize (Shader *shader, Texture *texture)
{
	CHECK_NULLPTR (shader);
	CHECK_NULLPTR (texture);

	m_shader = shader;
	m_texture = texture;

	return true;
}

template <typename VertexT, typename IndexT>
void Sprite <VertexT, IndexT>::Render (ID3D11DeviceContext *deviceContext)
{
	CHECK_THIS ();

	m_texture->Render (deviceContext);
	m_shader->Render (deviceContext);
	SetCBMatrix ();
	m_vertexBuffer.Render (deviceContext);
}

template <typename VertexT, typename IndexT>
void Sprite <VertexT, IndexT>::SetCBMatrix ()
{
	ID3D11DeviceContext *deviceContext = DXManager::GetDeviceContext ();

	m_WVPMatrixes->m_World  = m_orthoTransform;
	m_WVPMatrixes->m_World *= m_posTransform;
	m_WVPMatrixes->UpdateSubresource (deviceContext, m_CBWVPMatrixes);

	deviceContext->VSSetConstantBuffers (0, 1, &m_CBWVPMatrixes);
}

template <typename VertexT, typename IndexT>
void Sprite <VertexT, IndexT>::Move (float x, float y, float z)
{
	m_posTransform *= XMMatrixTranslation (x, y, z);
}

template <typename VertexT, typename IndexT>
inline void Sprite<VertexT, IndexT>::RotateX (float angle)
{
	m_orthoTransform *= XMMatrixRotationX (angle);
}

template <typename VertexT, typename IndexT>
inline void Sprite <VertexT, IndexT>::RotateY (float angle)
{
	m_orthoTransform *= XMMatrixRotationY (angle);
}

template <typename VertexT, typename IndexT>
inline void Sprite<VertexT, IndexT>::RotateZ (float angle)
{
	m_orthoTransform *= XMMatrixRotationZ (angle);
}

template <typename VertexT, typename IndexT>
inline void Sprite <VertexT, IndexT>::ScaleUp (float ScaleUpX, float ScaleUpY, float ScaleUpZ)
{
	m_orthoTransform *= XMMatrixScaling (ScaleUpX, ScaleUpY, ScaleUpZ);
}

template <typename VertexT, typename IndexT>
inline void Sprite <VertexT, IndexT>::SetTexture (Texture *texture)
{
	m_texture = texture;
}