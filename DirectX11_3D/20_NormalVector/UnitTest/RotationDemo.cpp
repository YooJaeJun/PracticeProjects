#include "stdafx.h"
#include "RotationDemo.h"

void RotationDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 0, -5.0f);

	shader = new Shader(L"09_World.fx");
	
	//vertices[0].Position = Vector3(+0.0f, +0.0f, 0.0f);
	//vertices[1].Position = Vector3(+0.0f, +0.5f, 0.0f);
	//vertices[2].Position = Vector3(+0.5f, +0.0f, 0.0f);
	//vertices[3].Position = Vector3(+0.5f, +0.0f, 0.0f);
	//vertices[4].Position = Vector3(+0.0f, +0.5f, 0.0f);
	//vertices[5].Position = Vector3(+0.5f, +0.5f, 0.0f);


	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = Vector3(-0.5f, +0.5f, 0.0f);
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

void RotationDemo::Destroy()
{
	SafeDelete(shader);

	SafeRelease(vertexBuffer);
}

void RotationDemo::Update()
{
	if (Keyboard::Get()->Press(VK_RIGHT))
	{
		z += 20 * Time::Delta();
	}
	else if (Keyboard::Get()->Press(VK_LEFT))
	{
		z -= 20 * Time::Delta();
	}

	D3DXMatrixRotationZ(&world, Math::ToRadian(z));
}

void RotationDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());


	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6);
}
