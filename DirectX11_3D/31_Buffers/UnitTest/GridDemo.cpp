#include "stdafx.h"
#include "GridDemo.h"

void GridDemo::Initialize()
{
	shader = new Shader(L"10_World.fx");
	
	
	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];

	for (UINT y = 0; y <= height; y++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			UINT i = (width + 1) * y + x;

			vertices[i].Position.x = (float)x;
			vertices[i].Position.y = 0.0f;
			vertices[i].Position.z = (float)y;
		}
	}

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	
	
	indexCount = (width * height) * 6;
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1) * y + x;
			indices[index + 1] = (width + 1) * (y + 1) + x;
			indices[index + 2] = (width + 1) * y + x + 1;
			indices[index + 3] = (width + 1) * y + x + 1;
			indices[index + 4] = (width + 1) * (y + 1) + x;
			indices[index + 5] = (width + 1) * (y + 1) + x + 1;

			index += 6;
		}
	}
	

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
	
	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);


	D3DXMatrixIdentity(&world);
}

void GridDemo::Destroy()
{
	SafeDelete(shader);

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void GridDemo::Update()
{
	
}

void GridDemo::Render()
{
	shader->AsScalar("Index")->SetInt(0);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());


	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	shader->DrawIndexed(0, 1, indexCount);
}