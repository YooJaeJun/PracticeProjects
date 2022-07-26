#include "framework.h"

GameObject::GameObject()
{
	position.x = 0.0f;
	position.y = 0.0f;
	scale.x = 1.0f;
	scale.y = 1.0f;
	rotation = 0.0f;
	rotation2 = 0.0f;

	isAxis = false;

	p = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	S = Matrix::CreateScale(scale.x, scale.y, 1.0f);
	R = Matrix::CreateRotationZ(rotation);
	T = Matrix::CreateTranslation(position.x, position.y, 0.0f);
	R2 = Matrix::CreateRotationZ(rotation2);

	RT = R * T * R2;

	if (p) RT *= *p;

	W = S * RT;
}

void GameObject::Render()
{
	if (isAxis)
	{
		// x��
		axis->position = GetWorldPos();
		axis->rotation = DirToRadian(GetRight());
		axis->scale.x = scale.x;
		axis->Update();
		axis->Render();

		// y��
		axis->rotation = DirToRadian(GetDown());
		axis->scale.x = scale.y;	// ���簢�� ���� ���� ���� �ٸ� ����
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
