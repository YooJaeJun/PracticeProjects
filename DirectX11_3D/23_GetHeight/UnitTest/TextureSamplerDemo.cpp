#include "stdafx.h"
#include "TextureSamplerDemo.h"

void TextureSamplerDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 0, -0.5f);

	shader = new Shader(L"18_TextureSampler.fx");
	
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0, 1);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 0);

	//vertices[0].Uv = Vector2(0.0f, 1.0f);
	//vertices[1].Uv = Vector2(0.0f, 0.0f);
	//vertices[2].Uv = Vector2(0.5f, 1.0f);
	//vertices[3].Uv = Vector2(0.5f, 0.0f);

	//vertices[0].Uv = Vector2(0, 2);
	//vertices[1].Uv = Vector2(0, 0);
	//vertices[2].Uv = Vector2(2, 2);
	//vertices[3].Uv = Vector2(2, 0);



	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(VertexTexture) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}


	D3DXMatrixIdentity(&world);

	texture = new Texture(L"Box.png");
}

void TextureSamplerDemo::Destroy()
{
	SafeDelete(shader);

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);

	SafeDelete(texture);
}

void TextureSamplerDemo::Update()
{
	static UINT filter = 0;
	ImGui::InputInt("Filter", (int *)&filter);
	filter %= 2;

	shader->AsScalar("Filter")->SetInt(filter);


	static UINT address = 0;
	ImGui::InputInt("Address", (int *)&address);
	filter %= 4;

	shader->AsScalar("Address")->SetInt(address);
}

void TextureSamplerDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsSRV("Map")->SetResource(texture->SRV());


	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->DrawIndexed(0, 0, 6);
	//shader->DrawIndexed(0, 1, 6); //Filter
	//shader->DrawIndexed(0, 2, 6); //Address
}
