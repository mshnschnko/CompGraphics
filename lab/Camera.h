#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera {
public:
	HRESULT Init();

	void Frame();

	void GetBaseViewMatrix(XMMATRIX& viewMatrix);

private:
	XMMATRIX viewMatrix;
	XMFLOAT3 pointOfInterest;

	float distanceToPoint;
	float phi;
	float theta;
};