#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#include "timer.h"

using namespace DirectX;

struct PostprocessingCB {
	XMINT4 params; // x - use posteffect, y - screen width, z - screen height
};

class Postprocessing {
public:
	HRESULT Init(ID3D11Device* device, HWND hwnd, int screenWidth, int screenHeight);

	void Release();

	void Render(ID3D11DeviceContext* context, ID3D11ShaderResourceView* sourceTexture, ID3D11RenderTargetView* renderTarget, D3D11_VIEWPORT viewport);

	bool Frame(ID3D11DeviceContext* context, bool usePosteffect);

	void Resize(int screenWidth, int screenHeight);

private:
	ID3D11VertexShader* g_pVertexShader = nullptr;
	ID3D11PixelShader* g_pPixelShader = nullptr;
	ID3D11SamplerState* g_pSamplerState = nullptr;
	ID3D11Buffer* g_pPostprocessingCB = nullptr;

	int m_screenWidth;
	int m_screenHeight;
};