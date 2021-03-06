#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>   // ���������� ����� ���������
#include <xnamath.h>
//#include "resource.h"
#include "AddFunc.h"

const float _size = 1;

struct SimpleVertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

HINSTANCE				g_hInstance = nullptr;
HWND					g_hWnd = nullptr;

D3D_DRIVER_TYPE			g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL		g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*			g_device = nullptr;
ID3D11DeviceContext*	g_deviceContext = nullptr;
IDXGISwapChain*			g_pSwapChain = nullptr;
ID3D11RenderTargetView*	g_pRenderTargetView = nullptr;

ID3D11VertexShader*		g_pVertexShader = nullptr;
ID3D11PixelShader*		g_pPixelShader = nullptr;
ID3D11InputLayout*		g_pVertexLayout = nullptr;
ID3D11Buffer*			g_pVertexBuffer = nullptr;
ID3D11Buffer*			g_pIndexBuffer = nullptr;
ID3D11Buffer*			g_pConstantBuffer = nullptr;

XMMATRIX g_World;
XMMATRIX g_View;
XMMATRIX g_Projection;

HRESULT InitWindow (HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice ();
HRESULT InitGeometry ();
HRESULT InitMatrixes ();

void SetMatrixes ();
void CleanupDevice ();
void Render ();
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT CompileShaderFromFile (LPCSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
							   ID3DBlob **ppBlobOut);

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER (hInstance);
	UNREFERENCED_PARAMETER (hPrevInstance);

	if (FAILED (InitWindow (hInstance, nCmdShow)))
	{
		PRINT_DEBUG_INFO;
		return 0;
	}

	if (FAILED (InitDevice ()))
	{
		PRINT_DEBUG_INFO;
		CleanupDevice ();
		return 0;
	}
	
	if (FAILED (InitGeometry ()))
	{
		PRINT_DEBUG_INFO;
		CleanupDevice ();
		return 0;
	}

	if (FAILED (InitMatrixes ()))
	{
		CleanupDevice ();
		PRINT_DEBUG_INFO;
		return 0;
	}

	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage (&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&msg);
			DispatchMessage	 (&msg);
		}
		else
		{
			SetMatrixes ();
			Render ();
		}
	}

	CleanupDevice ();

	return (int) msg.wParam;
}

HRESULT InitWindow (HINSTANCE hInstance, int nCmdShow)
{
	const char *pIcon = "Resources\\Plazma-3.jpg";

	WNDCLASSEX wcex = {0};
	ZeroMemory (&wcex, sizeof (wcex));
	wcex.cbSize = sizeof (WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon (hInstance, (LPCTSTR) pIcon);
	wcex.hCursor = LoadCursor (hInstance, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "MyWindowClass";
	wcex.hIconSm = LoadIcon (wcex.hInstance, (LPCTSTR) pIcon);

	if (!RegisterClassEx (&wcex))
	{
		PRINT_DEBUG_INFO;
		return E_FAIL;
	}
	g_hInstance = hInstance;
	RECT rect = {0, 0, 1920 / _size, 1080 / _size};
	AdjustWindowRect (&rect, WS_OVERLAPPEDWINDOW, FALSE);

	g_hWnd = CreateWindow ("MyWindowClass", "������� DX11",
						   WS_OVERLAPPEDWINDOW,
						   CW_USEDEFAULT, CW_USEDEFAULT, 
						   rect.right - rect.left, rect.bottom - rect.top, 
						   nullptr, nullptr, hInstance, nullptr);
	if (g_hWnd == nullptr)
	{
		PRINT_DEBUG_INFO;
		return E_FAIL;
	}

	ShowWindow (g_hWnd, nCmdShow);

	return S_OK;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps = {0};
	HDC hDC = nullptr;

	switch (message)
	{
		case WM_PAINT:
			hDC = BeginPaint (hWnd, &ps);
			EndPaint (hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage (0);
			break;
		default:
			return DefWindowProc (hWnd, message, wParam, lParam);
	}

	return 0;
}

HRESULT InitDevice ()
{
	HRESULT hr = S_OK;

	RECT rect = {0};
	GetClientRect (g_hWnd, &rect);
	UINT width = rect.right - rect.left;
	UINT height = rect.bottom - rect.top;
	UINT createDeviceFlags = 0;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes = ARRAYSIZE (driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE (featureLevels);

	DXGI_SWAP_CHAIN_DESC sd = {0};
	ZeroMemory (&sd, sizeof (sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 75;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;           
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain (nullptr, g_driverType, nullptr, createDeviceFlags,
											featureLevels, numFeatureLevels, D3D11_SDK_VERSION,
											&sd, &g_pSwapChain, &g_device, &g_featureLevel,
											&g_deviceContext);
		if (SUCCEEDED (hr))
		{
			break;
		}
	}
	
	if (FAILED (hr))
	{
		PRINT_DEBUG_INFO;
		return hr;
	}

	// RenderTargetOutput - �������� �����
	// RenderTargetView   - ������ �����

	ID3D11Texture2D *pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer (0, __uuidof (ID3D11Texture2D), (LPVOID *) &pBackBuffer);
	if (FAILED (hr))
	{
		PRINT_DEBUG_INFO;
		return hr;
	}

	hr = g_device->CreateRenderTargetView (pBackBuffer, nullptr, &g_pRenderTargetView);
	pBackBuffer->Release ();
	if (FAILED (hr))
	{
		PRINT_DEBUG_INFO;
		return hr;
	}

	g_deviceContext->OMSetRenderTargets (1, &g_pRenderTargetView, nullptr);
	
	D3D11_VIEWPORT viewport = {0};
	ZeroMemory (&viewport, sizeof (viewport));

	viewport.Width    = (float) width;
	viewport.Height   = (float) height;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	g_deviceContext->RSSetViewports (1, &viewport);

	return S_OK;
}

void Render ()
{
	float ClearColor[4] = {0, 0, 0, 1};
	g_deviceContext->ClearRenderTargetView (g_pRenderTargetView, ClearColor);

	g_deviceContext->VSSetShader (g_pVertexShader, nullptr, 0);
	g_deviceContext->VSSetConstantBuffers (0, 1, &g_pConstantBuffer);
	g_deviceContext->PSSetShader (g_pPixelShader,  nullptr, 0);

	g_deviceContext->DrawIndexed (18, 0, 0);

	g_pSwapChain->Present (0, 0);
}

HRESULT CompileShaderFromFile (LPCSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
							   ID3DBlob **ppBlobOut)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob *pErrorBlob = nullptr;
	
	hr = D3DX11CompileFromFile (szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
								dwShaderFlags, 0, nullptr, ppBlobOut, &pErrorBlob, nullptr);
	if (FAILED (hr))
	{
		if (pErrorBlob != nullptr)
		{
			OutputDebugStringA ((char *) pErrorBlob->GetBufferPointer ());
		}
		else
		{
			RELEASE (pErrorBlob);
		}

		return hr;
	}

	if (pErrorBlob != nullptr)
	{
		pErrorBlob->Release ();
	}

	return S_OK;
}

HRESULT InitGeometry ()
{

	HRESULT hr = S_OK;

	LPCSTR fileName = "Textures\\texture.fx";

	ID3DBlob *pVSBlob = nullptr;
	hr = CompileShaderFromFile (fileName, "VS", "vs_4_0", &pVSBlob);
	if (FAILED (hr))
	{
		MessageBox (nullptr, "Failed to create FX (VS) file.", "Error", MB_OK);
		return hr;
	}

	hr = g_device->CreateVertexShader (pVSBlob->GetBufferPointer (), pVSBlob->GetBufferSize (),
									   nullptr, &g_pVertexShader);
	if (FAILED (hr))
	{
		pVSBlob->Release ();
		return hr;
	}

	// ---------------------------------------------------------------------------------------
	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,						   D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof (SimpleVertex::pos), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT numElements = ARRAYSIZE (layout);

	hr = g_device->CreateInputLayout (layout, numElements, pVSBlob->GetBufferPointer (),
									  pVSBlob->GetBufferSize (), &g_pVertexLayout);
	if (FAILED (hr))
	{
		return hr;
	}

	g_deviceContext->IASetInputLayout (g_pVertexLayout);

	// ------------------------------------------------------------------------------------------

	ID3DBlob *pPSBlob = nullptr;
	hr = CompileShaderFromFile (fileName, "PS", "ps_4_0", &pPSBlob);
	if (FAILED (hr))
	{
		MessageBox (nullptr, "Failed to create FX (PS) file.", "Error", MB_OK);
		return hr;
	}

	hr = g_device->CreatePixelShader (pPSBlob->GetBufferPointer (), pPSBlob->GetBufferSize (),
									  nullptr, &g_pPixelShader);
	pPSBlob->Release ();

	if (FAILED (hr))
	{
		return hr;
	}

	// ------------------------------------------------------------------------------------------
	
	SimpleVertex vert[] = {
		{XMFLOAT3 (-0.0f,  1.0f, +0.0f), XMFLOAT4 (1.0f, 0.0f, 0.0f, 1.0f)},

		{XMFLOAT3 (-0.5f,  0.0f, +0.5f), XMFLOAT4 (0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3 (-0.5f,  0.0f, -0.5f), XMFLOAT4 (0.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3 (+0.5f,  0.0f, -0.5f), XMFLOAT4 (1.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3 (+0.5f,  0.0f, +0.5f), XMFLOAT4 (1.0f, 1.0f, 0.0f, 1.0f)},
	};

	const UINT numVertex = ARRAYSIZE (vert);

	D3D11_BUFFER_DESC bd = {0};
	ZeroMemory (&bd, sizeof (bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof (SimpleVertex) * numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {0};
	ZeroMemory (&InitData, sizeof (InitData));
	InitData.pSysMem = vert;

	hr = g_device->CreateBuffer (&bd, &InitData, &g_pVertexBuffer);
	if (FAILED (hr))
	{
		return hr;
	}
	
	WORD indices[] =
	{
		0, 4, 1,
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,

		1, 4, 2,
		2, 3, 4
	};

	ZeroMemory (&bd, sizeof (bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof (indices);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = g_device->CreateBuffer (&bd, &InitData, &g_pIndexBuffer);
	if (FAILED (hr))
	{
		return hr;
	}

	// ---------------------------------------------------------------------------------------

	UINT stride = sizeof (SimpleVertex);
	UINT offset = 0;

	g_deviceContext->IASetVertexBuffers (0, 1, &g_pVertexBuffer, &stride, &offset);
	g_deviceContext->IASetIndexBuffer (g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	g_deviceContext->IASetPrimitiveTopology (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	// ---------------------------------------------------------------------------------------

	ZeroMemory (&bd, sizeof (bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof (ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = g_device->CreateBuffer (&bd, nullptr, &g_pConstantBuffer);
	if (FAILED (hr))
	{
		return hr;
	}

	return S_OK;
}

void CleanupDevice ()
{
	if (g_deviceContext != nullptr)
	{
		g_deviceContext->ClearState ();
	}

	RELEASE (g_pConstantBuffer);
	RELEASE (g_pVertexBuffer);
	RELEASE (g_pIndexBuffer);
	RELEASE (g_pPixelShader);
	RELEASE (g_pVertexLayout);
	RELEASE (g_pVertexShader);

	RELEASE (g_pRenderTargetView);
	RELEASE (g_pSwapChain);
	RELEASE (g_deviceContext);
	RELEASE (g_device);
}

HRESULT InitMatrixes ()
{
	RECT rect;
	GetClientRect (g_hWnd, &rect);
	UINT width = rect.right - rect.left;
	UINT height = rect.bottom - rect.top;

	g_World = XMMatrixIdentity ();

	XMVECTOR Eye = XMVectorSet (0.0f, 0.0f, -5.0f, 5.0f);
	XMVECTOR At  = XMVectorSet (0.0f, 1.0f,  0.0f, 0.0f);
	XMVECTOR Up  = XMVectorSet (0.0f, 1.0f,  0.0f, 0.0f);
	g_View = XMMatrixLookAtLH (Eye, At, Up);

	g_Projection = XMMatrixPerspectiveFovLH (XM_PIDIV4, width / (float) height, 0.01f, 100.0f);

	return S_OK;
}

void SetMatrixes ()
{
	static float time = 0.0f;

	if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		time += (float) XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart= 0;
		ULONGLONG dwTimeCur = GetTickCount64 ();
		if (dwTimeStart == 0)
		{
			dwTimeStart = dwTimeCur;
		}

		time = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	const float _speed = 2.0f;
	time *= _speed;

	g_World  = XMMatrixScaling (sin (time) * sin (time) + 0.2, 0.4 + cos (time) * cos (time), 1);
	g_World *= XMMatrixTranslation (2.0, 0, 0);
	g_World *= XMMatrixRotationY (-tan (time));
	/*g_World *= XMMatrixRotationZ (_speed * cos (time) * cos (time) * sin (time));
	g_World *= XMMatrixTranslation (_speed * cos (time),
									0.3 + _speed * cos (-2 * (double) time ) / 2.5,
									2 * sin (-_speed * (double) time));
									*/
	ConstantBuffer cb;
	cb.mWorld		= XMMatrixTranspose (g_World);
	cb.mView		= XMMatrixTranspose (g_View);
	cb.mProjection	= XMMatrixTranspose (g_Projection);

	g_deviceContext->UpdateSubresource (g_pConstantBuffer, 0, nullptr, &cb, 0, 0);
}