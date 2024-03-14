#pragma once

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

using namespace DirectX;

class Scene {
public:
    HRESULT Init(ID3D11Device* device, ID3D11DeviceContext* context, int screenWidth, int screenHeight);

    void Realese();

    void Resize(int screenWidth, int screenHeight);

    void Render(ID3D11DeviceContext* context);

    bool Frame(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos);

private:
    bool FrameCubes(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos);
    bool FramePlanes(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos);

    Cube cubes;
    Plane planes;
    Skybox skybox;

    float angle_velocity = XM_PIDIV2;
};