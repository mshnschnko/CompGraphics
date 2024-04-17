#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <directxmath.h>
#include <ctime>
#include <chrono>

#include "renderTexture.h"
#include "postprocessing.h"
#include "Camera.h"
#include "scene.h"


class Renderer {
public:
	static Renderer& GetInstance();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;

	HRESULT Init(const HWND& g_hWnd, const HINSTANCE& g_hInstance, UINT screenWidth, UINT screenHeight);

	bool Frame();

	void Render();

	void CleanupDevice();

	void ResizeWindow(const HWND& g_hWnd);

	void MouseMoved(int x, int y);

	void MouseRBPressed(bool pressed, int x, int y);

	void MouseWheel(int wheel);
private:
	HRESULT InitDevice(const HWND& g_hWnd);
	HRESULT InitBackBuffer();

	void Resize(UINT screenWidth, UINT screenHeight);

	Renderer() = default;

	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11Device1* g_pd3dDevice1 = nullptr;
	ID3D11DeviceContext* g_pImmediateContext = nullptr;
	ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	IDXGISwapChain1* g_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
	ID3D11Texture2D* g_pDepthBuffer = nullptr;
	ID3D11DepthStencilView* g_pDepthBufferDSV = nullptr;

	RenderTexture renderTexture;
	Postprocessing postprocessing;

	Camera camera;
	Scene scene;

	bool m_fixFrustumCulling;
	bool m_usePosteffect;
	const char* m_modes[3];
	int m_currentMode = DrawMode::GPU;

	long long m_totalFrameTime[3]; // 0 - CPU mode, 1 - instancing, 2 - GPU culling + instancing
	long long m_totalRenderTime[3];
	int m_frameCount[3]; // Frame count for every draw mode

	long long lastFrameTime = 0;
	long long lastRenderTime = 0;


	UINT m_width;
	UINT m_height;
	bool m_rbPressed;
	int m_prevMouseX;
	int m_prevMouseY;
	float angle_velocity = XM_PIDIV2;
};