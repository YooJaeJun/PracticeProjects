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

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WVPBuffer);	// WVPBuffer 최종행렬
		assert(SUCCEEDED(hr));
	}
	D3D->GetDC()->VSSetConstantBuffers(0, 1, &WVPBuffer);

	//CreateConstantBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Color);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //상수버퍼
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
	RX = Matrix::CreateRotationX(rotationX);	// 추가
	RY = Matrix::CreateRotationY(rotationY);	// 추가
	T = Matrix::CreateTranslation(position.x, position.y, 0.0f);
	R2 = Matrix::CreateRotationZ(rotation2);

	RT = R * RX * RY * T * R2;

	//P의 주소가 있으면
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
		axisObject->SetWorldPos(GetWorldPivot());	// GetWorldPivot() 중점. 최종행렬 W에서 가져옴. RT에서 가져오는 건 GetWorldPos()
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
		WVP = W * CAM->GetVP();		// V: 카메라 영향을 받는다.
		break;
	case SPACE::SCREEN:
		WVP = W * CAM->GetP();
		break;
	}

	WVP = WVP.Transpose();	// 전치행렬: 행 우선에서 열 우선으로 변경해줌. GPU 연산이 열 우선이 더 빠름
	{
		// subresource와 map 함수를 이용. CPU와 GPU의 중복 접근을 막음
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
		if (GetRight() == RIGHT) //회전X			// 1이나 0이나 0.5는 부동소수점 오차 없어서 == 비교 가능
		{
			Utility::RECT rc(GetWorldPivot(), scale);
			return IntersectRectCoord(rc, coord);
		}
		else //회전
		{
			Vector2 rcpivot = Vector2::Transform(pivot, S);		// 피벗 다시 원점 위치
			Utility::RECT rc1(rcpivot, scale);

			Matrix rcInverse = RT.Invert();
			coord = Vector2::Transform(coord, rcInverse);		// 마우스도 사각형의 체계로. SRT * (1/RT). scale만 남음

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
		//사각형과 사각형
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
		//사각형과 원
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
		//원과 사각형
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
		//원과 원
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
