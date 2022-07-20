#include "framework.h"

GameObject::GameObject()
{
	position.x = 0.0f;
	position.y = 0.0f;

	scale.x = 1.0f;
	scale.y = 1.0f;

	rotation = 0.0f;
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

}
