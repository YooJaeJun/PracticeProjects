#include "framework.h"

ObLine* GameObject::axisObject = nullptr;
ID3D11Buffer* GameObject::WVPBuffer = nullptr;
ID3D11Buffer* GameObject::colorBuffer = nullptr;
Shader* GameObject::basicShader = nullptr;
Shader* GameObject::imageShader = nullptr;

void GameObject::CreateStaticMember()
{
	//CreateConstantBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Matrix);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WVPBuffer);	// WVPBuffer �������
		assert(SUCCEEDED(hr));
	}
	D3D->GetDC()->VSSetConstantBuffers(0, 1, &WVPBuffer);

	//CreateConstantBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Color);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //�������
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}
	D3D->GetDC()->VSSetConstantBuffers(1, 1, &colorBuffer);

	basicShader = new Shader(L"1.Basic");
	imageShader = new Shader(L"2.Image");
	axisObject = new ObLine();
}

void GameObject::DeleteStaticMember()
{
	delete axisObject;
	delete basicShader;
	delete imageShader;
	WVPBuffer->Release();
	colorBuffer->Release();
}


GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;

	rotation = 0;
	rotationX = 0;
	rotationY = 0;
	rotation2 = 0;
	color = Color(0.5, 0.5, 0.5, 0.5);
	isVisible = true;
	isFilled = true;
	isAxis = false;
	P = nullptr;
	pivot = OFFSET_N;
	space = SPACE::WORLD;
	colOnOff = true;
}

void GameObject::Update()
{
	Pi = Matrix::CreateTranslation(pivot.x, pivot.y, 0.0f);
	S = Matrix::CreateScale(scale.x, scale.y, 1.0f);
	R = Matrix::CreateRotationZ(rotation);
	RX = Matrix::CreateRotationX(rotationX);	// �߰�
	RY = Matrix::CreateRotationY(rotationY);	// �߰�
	T = Matrix::CreateTranslation(position.x, position.y, 0.0f);
	R2 = Matrix::CreateRotationZ(rotation2);

	RT = R * RX * RY * T * R2;

	//P�� �ּҰ� ������
	if (P)
	{
		RT *= *P;
	}
	W = Pi * S * RT;

}

void GameObject::Render()
{
	if (isAxis)
	{
		//right
		axisObject->SetWorldPos(GetWorldPivot());	// GetWorldPivot() ����. ������� W���� ������. RT���� �������� �� GetWorldPos()
		axisObject->rotation = Utility::DirToRadian(GetRight());
		axisObject->scale.x = scale.x * 2.0f;
		axisObject->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		axisObject->Update();
		axisObject->Render();
		//up
		axisObject->rotation = Utility::DirToRadian(GetUp());
		axisObject->scale.x = scale.y * 2.0f;
		axisObject->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
		axisObject->Update();
		axisObject->Render();
	}
	switch (space)
	{
	case SPACE::WORLD:
		WVP = W * CAM->GetVP();		// V: ī�޶� ������ �޴´�.
		break;
	case SPACE::SCREEN:
		WVP = W * CAM->GetP();
		break;
	}

	WVP = WVP.Transpose();	// ��ġ���: �� �켱���� �� �켱���� ��������. GPU ������ �� �켱�� �� ����
	{
		// subresource�� map �Լ��� �̿�. CPU�� GPU�� �ߺ� ������ ����
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(WVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Matrix), &WVP, sizeof(Matrix));
		D3D->GetDC()->Unmap(WVPBuffer, 0);
	}
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Color), &color, sizeof(Color));
		D3D->GetDC()->Unmap(colorBuffer, 0);
	}
}

IntersectPos GameObject::Intersect(Vector2 coord)
{
	if (not colOnOff) return IntersectPos::none;
	
	if (collider == COLLIDER::RECT)
	{
		if (GetRight() == RIGHT) //ȸ��X			// 1�̳� 0�̳� 0.5�� �ε��Ҽ��� ���� ��� == �� ����
		{
			Utility::RECT rc(GetWorldPivot(), scale);
			return IntersectRectCoord(rc, coord);
		}
		else //ȸ��
		{
			Vector2 rcpivot = Vector2::Transform(pivot, S);		// �ǹ� �ٽ� ���� ��ġ
			Utility::RECT rc1(rcpivot, scale);

			Matrix rcInverse = RT.Invert();
			coord = Vector2::Transform(coord, rcInverse);		// ���콺�� �簢���� ü���. SRT * (1/RT). scale�� ����

			return IntersectRectCoord(rc1, coord);
		}
	
	}
	else if (collider == COLLIDER::CIRCLE)
	{
		Utility::CIRCLE cc(GetWorldPivot(), scale);
		return Utility::IntersectCircleCoord(cc, coord);
	}
	return IntersectPos::none;
}

IntersectPos GameObject::Intersect(GameObject* ob)
{
	if (colOnOff == false or ob->colOnOff == false) return IntersectPos::none;

	if (collider == COLLIDER::RECT)
	{
		//�簢���� �簢��
		if (ob->collider == COLLIDER::RECT)
		{
			if (GetRight() == RIGHT && ob->GetRight() == RIGHT)
			{
				Utility::RECT rc1(GetWorldPivot(), scale);
				Utility::RECT rc2(ob->GetWorldPivot(), ob->scale);
				return Utility::IntersectRectRect(rc1, rc2);
			}
			else
			{
				return Utility::IntersectRectRect(this, ob);
			}

		}
		//�簢���� ��
		else if (ob->collider == COLLIDER::CIRCLE)
		{
			if (GetRight() == RIGHT)
			{
				Utility::RECT rc1(GetWorldPivot(), scale);
				Utility::CIRCLE cc2(ob->GetWorldPivot(), ob->scale);
				return Utility::IntersectRectCircle(rc1, cc2);
			}
			else
			{
				Vector2 rc1pivot = Vector2::Transform(pivot, S);
				Utility::RECT rc1(rc1pivot, scale);
				Matrix rcInverse = RT.Invert();
				Vector2 cc2pivot = ob->GetWorldPivot();
				cc2pivot = Vector2::Transform(cc2pivot, rcInverse);
				Utility::CIRCLE cc2(cc2pivot, ob->scale);

				return IntersectRectCircle(rc1, cc2);
			}
		}
	}
	else if (collider == COLLIDER::CIRCLE)
	{
		//���� �簢��
		if (ob->collider == COLLIDER::RECT)
		{
			if (GetRight() == RIGHT)
			{
				Utility::RECT rc1(ob->GetWorldPivot(), ob->scale);
				Utility::CIRCLE cc2(GetWorldPivot(), scale);
				return Utility::IntersectRectCircle(rc1, cc2);
			}
			else
			{
				Vector2 rc1pivot = Vector2::Transform(ob->pivot, ob->S);
				Utility::RECT rc1(rc1pivot, ob->scale);
				Matrix rcInverse = ob->RT.Invert();
				Vector2 cc2pivot = GetWorldPivot();
				cc2pivot = Vector2::Transform(cc2pivot, rcInverse);
				Utility::CIRCLE cc2(cc2pivot, scale);

				return IntersectRectCircle(rc1, cc2);
			}
		}
		//���� ��
		else if (ob->collider == COLLIDER::CIRCLE)
		{
			Utility::CIRCLE cc1(GetWorldPivot(), scale);
			Utility::CIRCLE cc2(ob->GetWorldPivot(), ob->scale);
			return Utility::IntersectCircleCircle(cc1, cc2);
		}
	}
	return IntersectPos::none;
}

IntersectPos GameObject::IntersectScreenMouse(Vector2 coord)
{
	coord.y = app.GetHalfHeight() - coord.y;
	coord.x = coord.x - app.GetHalfWidth();
	return Intersect(coord);
}

void GameObject::SetWorldPos(Vector2 worldPos)
{
	if (!P)
	{
		position = worldPos;
	}
	else
	{
		Vector2 location = Vector2::Transform(worldPos, (*P).Invert());
		position = location;
	}
}

void GameObject::SetWorldPosX(float worldPosX)
{
	if (!P)
	{
		position.x = worldPosX;
	}
	else
	{
		Vector2 location = Vector2::Transform(Vector2(worldPosX, 0), (*P).Invert());
		position.x = location.x;
	}
}
void GameObject::SetWorldPosY(float worldPosY)
{
	if (!P)
	{
		position.y = worldPosY;
	}
	else
	{
		Vector2 location = Vector2::Transform(Vector2(0, worldPosY), (*P).Invert());
		position.y = location.y;
	}
}
void GameObject::MoveWorldPos(Vector2 Velocity)
{
	if (!P)
	{
		position += Velocity;
	}
	else
	{
		Vector2 locVelocity = Vector2::TransformNormal(Velocity, (*P).Invert());
		position += locVelocity;
	}
}
