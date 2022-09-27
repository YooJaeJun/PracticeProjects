#include "framework.h"

Camera::Camera()
{
    //ù ī�޶� ��ġ
    position.x = 0.0f;
    position.y = 0.0f;
    //����Ʈ
    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
    // ��
    coefScale = Vector3(1.0f, 1.0f, 1.0f);
}

void Camera::Set()
{
    //����� -> ���̵����
    V = Matrix::CreateTranslation(-position.x, -position.y, coefScale.z);
    // ũ�� ��� (���� �ܾƿ�)
    S = Matrix::CreateScale(Vector3(coefScale.x, coefScale.y, coefScale.z));
    //�������� -> �������      // ���� ���� ��� ���� ���� �� ��
    P = Matrix::CreateOrthographic(app.GetWidth(), app.GetHeight(), 0.0f, 10.0f);

    VP = V * S * P;
}

void Camera::Zoom(const float zDelta)
{
    coefScale.x += zDelta / 1200.0f;
    coefScale.y += zDelta / 1200.0f;
    coefScale.z += zDelta / 1200.0f;
    coefScale.x = Utility::Saturate(coefScale.x, 0.05f, 1.0f);
    coefScale.y = Utility::Saturate(coefScale.y, 0.05f, 1.0f);
    coefScale.z = Utility::Saturate(coefScale.z, 0.05f, 1.0f);
}

void Camera::ResizeScreen()
{
    // viewport.x = 200.0f;
    // viewport.y = 200.0f;
    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}
