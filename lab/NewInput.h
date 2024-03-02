#pragma once

#include <directxmath.h>
#include <dxgi.h>

using namespace DirectX;

class NewInput {
public:
	NewInput();
    HRESULT InitInputs(UINT screenWidth, UINT screenHeight);
    void MouseRBPressed(bool pressed, int x, int y);
    XMFLOAT3 MouseMoved(int x, int y, float angle_velocity);
    void MouseWheel(int delta);
    void KeyPressed(int keyCode);

private:
    UINT m_width;
    UINT m_height;
    bool m_rbPressed;
    int m_prevMouseX;
    int m_prevMouseY;
    bool m_rotateModel;
    double m_angle;
};