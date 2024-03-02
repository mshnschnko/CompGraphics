#include "NewInput.h"

NewInput::NewInput() : m_rbPressed(false), m_prevMouseX(0), m_prevMouseY(0), m_rotateModel(false), m_angle(0.0) {}

HRESULT NewInput::InitInputs(UINT screenWidth, UINT screenHeight) {
    m_width = screenWidth;
    m_height = screenHeight;
    return S_OK;
}

void NewInput::MouseRBPressed(bool pressed, int x, int y) {
    m_rbPressed = pressed;
    
    if (m_rbPressed) {
        m_prevMouseX = x;
        m_prevMouseY = y;
    }
}

XMFLOAT3 NewInput::MouseMoved(int x, int y, float angle_velocity) {
    if (m_rbPressed)
    {
        float dx = -(float)(x - m_prevMouseX) * angle_velocity;
        float dy = (float)(y - m_prevMouseY) * angle_velocity;

        //m_camera.phi += dx;
        //m_camera.theta += dy;
        //m_camera.theta = std::min(std::max(m_camera.theta, -(float)M_PI / 2), (float)M_PI / 2);

        m_prevMouseX = x;
        m_prevMouseY = y;
        return XMFLOAT3(dx, dy, 0.0);
    }
    else
        return XMFLOAT3(0.0, 0.0, 0.0);
}
//
//void NewInput::MouseWheel(int delta)
//{
//    m_camera.r -= delta / 100.0f;
//    if (m_camera.r < 1.0f)
//    {
//        m_camera.r = 1.0f;
//    }
//}