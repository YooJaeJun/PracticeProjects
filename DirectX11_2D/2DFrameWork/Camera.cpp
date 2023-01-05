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
    zoomFactor = Vector3(1.0f, 1.0f, 1.0f);
}

void Camera::Set()
{
    //����� -> ���̵����
    V = Matrix::CreateTranslation(-position.x, -position.y, -1.0f);
    // ũ�� ��� (���� �ܾƿ�)
    S = Matrix::CreateScale(Vector3(zoomFactor.x, zoomFactor.y, zoomFactor.z));

    //�������� -> �������      // ���� ���� ��� ���� ���� �� ��
    P = Matrix::CreateOrthographic(app.GetWidth(), app.GetHeight(), 0.0f, 10.0f);

    VP = V * S * P;
}

void Camera::Zoom(const float zDelta)
{
    zoomFactor.x += zDelta / 1200.0f;
    zoomFactor.y += zDelta / 1200.0f;
    zoomFactor.z += zDelta / 1200.0f;
    zoomFactor.x = Utility::Saturate(zoomFactor.x, 0.08f, 1.0f);
    zoomFactor.y = Utility::Saturate(zoomFactor.y, 0.08f, 1.0f);
    zoomFactor.z = Utility::Saturate(zoomFactor.z, 0.08f, 1.0f);
}

void Camera::ResizeScreen()
{
    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}
