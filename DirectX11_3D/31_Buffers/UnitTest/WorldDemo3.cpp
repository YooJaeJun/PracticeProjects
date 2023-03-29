#include "stdafx.h"
#include "WorldDemo3.h"

void WorldDemo3::Initialize()
{
	shader = new Shader(L"10_World.fx");
	
	CreateVertex();
	CreateVertex2();
}

void WorldDemo3::Destroy()
{
	SafeDelete(shader);

	SafeRelease(vertexBuffer);
	SafeRelease(vertexBuffer2);
}

void WorldDemo3::Update()
{
	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
		{
			position.x += 2.0f * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT))
		{
			position.x -= 2.0f * Time::Delta();
		}
	}
	else
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
		{
			scale.x += 2.0f * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT))
		{
			scale.x -= 2.0f * Time::Delta();
		}
	}

	Matrix S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * T;


/*	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
		{
			world._41 += 2.0f * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT))
		{
			world._41 -= 2.0f * Time::Delta();
		}
	}
	else
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
		{
			world2._41 += 2.0f * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT))
		{
			world2._41 -= 2.0f * Time::Delta();
		}
	}*/		
}

void WorldDemo3::Render()
{
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());


	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	shader->AsScalar("Index")->SetInt(0);
	shader->AsMatrix("World")->SetMatrix(world);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	shader->Draw(0, 0, 6);

	
	shader->AsScalar("Index")->SetInt(1);
	shader->AsMatrix("World")->SetMatrix(world2);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer2, &stride, &offset);

	shader->Draw(0, 0, 6);
}

void WorldDemo3::CreateVertex()
{
	vertices[0].Position = Vector3(+0.0f, +0.0f, 0.0f);
	vertices[1].Position = Vector3(+0.0f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, +0.0f, 0.0f);

	vertices[3].Position = Vector3(+0.5f, +0.0f, 0.0f);
	vertices[4].Position = Vector3(+0.0f, +0.5f, 0.0f);
	vertices[5].Position = Vector3(+0.5f, +0.5f, 0.0f);



	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));


	D3DXMatrixIdentity(&world);
}

void WorldDemo3::CreateVertex2()
{
	vertices2[0].Position = Vector3(+0.0f, +0.0f, 0.0f);
	vertices2[1].Position = Vector3(+0.0f, +0.5f, 0.0f);
	vertices2[2].Position = Vector3(+0.5f, +0.0f, 0.0f);

	vertices2[3].Position = Vector3(+0.5f, +0.0f, 0.0f);
	vertices2[4].Position = Vector3(+0.0f, +0.5f, 0.0f);
	vertices2[5].Position = Vector3(+0.5f, +0.5f, 0.0f);



	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices2;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer2));


	D3DXMatrixIdentity(&world2);
}
