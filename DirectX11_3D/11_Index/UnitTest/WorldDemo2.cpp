#include "stdafx.h"
#include "WorldDemo2.h"

void WorldDemo2::Initialize()
{
	shader = new Shader(L"10_World.fx");
	
	//Local
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


	for(int i = 0; i < 3; i++)
		D3DXMatrixIdentity(&world[i]);
}

void WorldDemo2::Destroy()
{
	SafeDelete(shader);

	SafeRelease(vertexBuffer);
}

void WorldDemo2::Update()
{
	ImGui::InputInt("Select", (int *)&index);
	index %= 3;

	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
		{
			world[index]._41 += 2.0f * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT))
		{
			world[index]._41 -= 2.0f * Time::Delta();
		}
	}
	else
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
		{
			world[index]._22 += 2.0f * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT))
		{
			world[index]._22 -= 2.0f * Time::Delta();
		}
	}		
}

void WorldDemo2::Render()
{
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());


	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	shader->AsScalar("Index")->SetInt(0);
	shader->AsMatrix("World")->SetMatrix(world[0]);
	shader->Draw(0, 0, 6);

	shader->AsScalar("Index")->SetInt(1);
	shader->AsMatrix("World")->SetMatrix(world[1]);
	shader->Draw(0, 0, 6);

	shader->AsScalar("Index")->SetInt(2);
	shader->AsMatrix("World")->SetMatrix(world[2]);
	shader->Draw(0, 0, 6);
}
