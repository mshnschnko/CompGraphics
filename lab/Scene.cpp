#include "Scene.h"

HRESULT Scene::Init(ID3D11Device* device, ID3D11DeviceContext* context, int screenWidth, int screenHeight) {
    std::vector<XMFLOAT4> cubePositions = std::vector<XMFLOAT4>(MAX_CUBES);
    for (int i = 0; i < MAX_CUBES; i++) {
        cubePositions[i] = XMFLOAT4(
            (rand() / (float)(RAND_MAX + 1) * SCENE_SIZE - SCENE_SIZE / 2.f),
            (rand() / (float)(RAND_MAX + 1) * SCENE_SIZE - SCENE_SIZE / 2.f),
            (rand() / (float)(RAND_MAX + 1) * SCENE_SIZE - SCENE_SIZE / 2.f), 1.f);
    }
    HRESULT hr = cube.Init(device, context, screenWidth, screenHeight, { L"./196.dds", L"./shrek1_1.dds"}, L"./196_norm.dds", 32.f, cubePositions);
    if (FAILED(hr))
        return hr;

    std::vector<XMFLOAT4> planeColors = {
      XMFLOAT4(1.f, 0.f, 0.f, 0.5f),
      XMFLOAT4(0.f, 1.f, 0.f, 0.5f),
      XMFLOAT4(0.f, 0.f, 1.f, 0.5f),
    };

    hr = planes.Init(device, context, screenWidth, screenHeight, 3, planeColors);
    if (FAILED(hr))
        return hr;

    hr = skybox.Init(device, context, screenWidth, screenHeight);

    std::vector<XMFLOAT4> colors = std::vector<XMFLOAT4>(MAX_LIGHTS);
    std::vector<XMFLOAT4> positions = std::vector<XMFLOAT4>(MAX_LIGHTS);

    for (int i = 0; i < MAX_LIGHTS; i++) {
        colors[i] = XMFLOAT4(
            (float)(0.5f + rand() / (float)(RAND_MAX + 1) * 0.5f),
            (float)(0.5f + rand() / (float)(RAND_MAX + 1) * 0.5f),
            (float)(0.5f + rand() / (float)(RAND_MAX + 1) * 0.5f), 1.f);
        positions[i] = XMFLOAT4(
            (rand() / (float)(RAND_MAX + 1) * SCENE_SIZE - SCENE_SIZE / 2.f),
            (rand() / (float)(RAND_MAX + 1) * SCENE_SIZE - SCENE_SIZE / 2.f),
            (rand() / (float)(RAND_MAX + 1) * SCENE_SIZE - SCENE_SIZE / 2.f), 1.f);
    }
    hr = lights.Init(device, context, screenWidth, screenHeight, colors, positions);

    return hr;
}

void Scene::Release() {
    cube.Release();
    planes.Release();
    skybox.Release();
    lights.Release();
}

void Scene::Render(ID3D11DeviceContext* context) {
    cube.Render(context);
    lights.Render(context);
    skybox.Render(context);
    planes.Render(context);
}

bool Scene::FramePlanes(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos) {
    auto duration = Timer::GetInstance().Clock();
    std::vector<XMMATRIX> worldMatricies = std::vector<XMMATRIX>(3);

    worldMatricies[0] = XMMatrixTranslation(1.25f, (float)(3.5 * sqrtf(2.0) * cos(duration) / (1.0 + sin(duration) * sin(duration))), (float)(3.5*sqrtf(2.0)*sin(duration)*cos(duration)/(1+ sin(duration)* sin(duration))));
    worldMatricies[1] = XMMatrixTranslation(-1.25f, (float)(sin(duration * 2) * 2.0), (float)(sin(duration * 2) * -2.0));
    worldMatricies[2] = XMMatrixTranslation(1.5f, (float)(sin(duration * 2) * 2.0), (float)(sin(duration * 2) * 2.0));

    bool failed = planes.Frame(context, worldMatricies, viewMatrix, projectionMatrix, cameraPos, lights);

    return failed;
}

bool Scene::Frame(ID3D11DeviceContext* context, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos, bool useFrustumCulling) {
    bool failed = cube.Frame(context, viewMatrix, projectionMatrix, cameraPos, lights, useFrustumCulling);
    if (failed)
        return false;

    failed = FramePlanes(context, viewMatrix, projectionMatrix, cameraPos);
    if (failed)
        return false;

    failed = skybox.Frame(context, viewMatrix, projectionMatrix, cameraPos);
    if (failed)
        return false;

    failed = lights.Frame(context, viewMatrix, projectionMatrix, cameraPos);

    return failed;
}

void Scene::Resize(int screenWidth, int screenHeight) {
    cube.Resize(screenWidth, screenHeight);
    planes.Resize(screenWidth, screenHeight);
    skybox.Resize(screenWidth, screenHeight);
    lights.Resize(screenWidth, screenHeight);
};