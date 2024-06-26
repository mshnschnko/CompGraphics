#pragma once

#include <windows.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <d3d11.h>
#include <directxmath.h>
#include <string>
#include <vector>

#include "skybox.h"
#include "Cube.h"
#include "Plane.h"
#include "timer.h"
#include "texture.h"
#include "Light.h"

using namespace DirectX;

class Scene {
public:
    HRESULT Init(ID3D11Device* device, ID3D11DeviceContext* context, int screenWidth, int screenHeight);

    void Release();

    void Resize(int screenWidth, int screenHeight);

    void Render(ID3D11DeviceContext* context, int drawMode);

    bool Frame(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos, bool fixFrustumCulling, int drawMode);


    int GetRenderedCount() { return cube.GetRenderedCubesCount(); };
private:
    bool FramePlanes(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos);

    Cube cube;
    Plane planes;
    Skybox skybox;
    Light lights;

    float angle_velocity = XM_PIDIV2;
};