#include "framework.h"

GameObject::GameObject()
{
	position.x = 0.0f;
	position.y = 0.0f;
	scale.x = 1.0f;
	scale.y = 1.0f;
	rotation = 0.0f;
	isAxis = false;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	S = Matrix::CreateScale(scale.x, scale.y, 1.0f);
	R = Matrix::CreateRotationZ(rotation);
	T = Matrix::CreateTranslation(position.x, position.y, 0.0f);

	W = S * R * T;
}

void GameObject::Render()
{
	if (isAxis)
	{
		// x축
		axis->position = position;
		axis->rotation = rotation;
		axis->scale.x = scale.x;
		axis->Update();
		axis->Render();

		// y축
		axis->rotation = rotation + DIV2PI;
		axis->scale.x = scale.y;	// 직사각형 같이 가로 세로 다른 도형
		axis->Update();
		axis->Render();
	}
}

ObLine* GameObject::axis = nullptr;

void GameObject::CreateStaticMember()
{
	axis = new ObLine();
}

void GameObject::DeleteStaticMember()
{
	delete axis;
}
