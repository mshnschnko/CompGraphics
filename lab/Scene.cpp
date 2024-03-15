#include "Scene.h"

HRESULT Scene::Init(ID3D11Device* device, ID3D11DeviceContext* context, int screenWidth, int screenHeight) {
    std::vector<XMFLOAT4> colors = {
      XMFLOAT4(1.f, 0.f, 0.f, 1.f),
      XMFLOAT4(0.f, 1.f, 0.f, 1.f),
      XMFLOAT4(0.f, 0.f, 1.f, 1.f),
    };

    HRESULT hr = cubes.Init(device, context, screenWidth, screenHeight, 2);
    if (FAILED(hr))
        return hr;

    hr = planes.Init(device, context, screenWidth, screenHeight, 3, colors);
    if (FAILED(hr))
        return hr;

    hr = skybox.Init(device, context, screenWidth, screenHeight);

    return hr;
}

void Scene::Realese() {
    cubes.Realese();
    planes.Realese();
    skybox.Realese();
}

void Scene::Render(ID3D11DeviceContext* context) {
    cubes.Render(context);
    skybox.Render(context);
    planes.Render(context);
}

bool Scene::FrameCubes(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos) {
    auto duration = Timer::GetInstance().Clock();
    std::vector<XMMATRIX> worldMatricies = std::vector<XMMATRIX>(2);

    worldMatricies[0] = XMMatrixRotationY((float)duration * angle_velocity);
    worldMatricies[1] = XMMatrixRotationY((float)duration * angle_velocity * 0.25f) * XMMatrixTranslation((float)sin(duration) * 3.0f, 0.0f, (float)cos(duration) * 3.0f);
    bool failed = cubes.Frame(context, worldMatricies, viewMatrix, projectionMatrix, cameraPos);

    return failed;
}

bool Scene::FramePlanes(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos) {
    auto duration = Timer::GetInstance().Clock();
    std::vector<XMMATRIX> worldMatricies = std::vector<XMMATRIX>(3);

    worldMatricies[0] = XMMatrixTranslation(1.25f, (float)(3.5 * sqrtf(2.0) * cos(duration) / (1.0 + sin(duration) * sin(duration))), (float)(3.5*sqrtf(2.0)*sin(duration)*cos(duration)/(1+ sin(duration)* sin(duration))));
    worldMatricies[1] = XMMatrixTranslation(-1.25f, (float)(sin(duration * 2) * 2.0), (float)(sin(duration * 2) * -2.0));
    worldMatricies[2] = XMMatrixTranslation(1.5f, (float)(sin(duration * 2) * 2.0), (float)(sin(duration * 2) * 2.0));

    bool failed = planes.Frame(context, worldMatricies, viewMatrix, projectionMatrix, cameraPos);

    return failed;
}

bool Scene::Frame(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos) {
    bool failed = FrameCubes(context, viewMatrix, projectionMatrix, cameraPos);
    if (failed)
        return false;

    failed = FramePlanes(context, viewMatrix, projectionMatrix, cameraPos);
    if (failed)
        return false;

    failed = skybox.Frame(context, viewMatrix, projectionMatrix, cameraPos);

    return failed;
}

void Scene::Resize(int screenWidth, int screenHeight) {
    cubes.Resize(screenWidth, screenHeight);
    planes.Resize(screenWidth, screenHeight);
    skybox.Resize(screenWidth, screenHeight);
};