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
}

void Camera::Set()
{
    //����� -> ���̵����
    V = Matrix::CreateTranslation(-position.x, -position.y, 0.0f);
    //�������� -> �������
    P = Matrix::CreateOrthographic(app.GetWidth(), app.GetHeight(), 0.0f, 10.0f);

    VP = V * P;
}

void Camera::ResizeScreen()
{
    /*viewport.x = 200.0f;
    viewport.y = 200.0f;*/

    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}
