#include "framework.h"

Camera::Camera()
{
    //첫 카메라 위치
    position.x = 0.0f;
    position.y = 0.0f;
    //뷰포트
    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
    // 줌
    coefScale = Vector3(1.0f, 1.0f, 1.0f);
}

void Camera::Set()
{
    //뷰행렬 -> 역이동행렬
    V = Matrix::CreateTranslation(-position.x, -position.y, coefScale.z);
    // 크기 행렬 (줌인 줌아웃)
    S = Matrix::CreateScale(Vector3(coefScale.x, coefScale.y, coefScale.z));
    //프로젝션 -> 투영행렬      // 원근 투영 대신 직교 투영 쓸 것
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
