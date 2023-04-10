#include "Framework.h"
#include "DebugLine.h"

DebugLine* DebugLine::instance = NULL;

void DebugLine::Create()
{
	assert(instance == NULL);

	instance = new DebugLine();
}

void DebugLine::Delete()
{
	SafeDelete(instance);
}

DebugLine * DebugLine::Get()
{
	assert(instance != NULL);

	return instance;
}

void DebugLine::RenderLine(Vector3 & start, Vector3 & end)
{
	RenderLine(start, end, Color(0, 1, 0, 1));
}

void DebugLine::RenderLine(Vector3 & start, Vector3 & end, float r, float g, float b)
{
	RenderLine(start, end, Color(r, g, b, 1));
}

void DebugLine::RenderLine(float x, float y, float z, float x2, float y2, float z2)
{
	RenderLine(Vector3(x, y, z), Vector3(x2, y2, z2), Color(0, 1, 0, 1));
}

void DebugLine::RenderLine(float x, float y, float z, float x2, float y2, float z2, float r, float g, float b)
{
	RenderLine(Vector3(x, y, z), Vector3(x2, y2, z2), Color(r, g, b, 1));
}

void DebugLine::RenderLine(float x, float y, float z, float x2, float y2, float z2, Color & color)
{
	RenderLine(Vector3(x, y, z), Vector3(x2, y2, z2), color);
}

void DebugLine::RenderLine(Vector3 & start, Vector3 & end, Color & color)
{
	vertices[drawCount].Color = color;
	vertices[drawCount++].Position = start;

	vertices[drawCount].Color = color;
	vertices[drawCount++].Position = end;
}

void DebugLine::Update()
{
	Matrix world;
	D3DXMatrixIdentity(&world);

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void DebugLine::Render()
{
	if (drawCount < 1) return;

	D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(VertexColor) * drawCount, 0);


	UINT stride = sizeof(VertexColor);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	shader->Draw(0, 0, drawCount);


	drawCount = 0;
	ZeroMemory(vertices, sizeof(VertexColor) * MAX_DEBUG_LINE);
}

DebugLine::DebugLine()
{
	shader = new Shader(L"20_DebugLine.fx");

	vertices = new VertexColor[MAX_DEBUG_LINE];
	ZeroMemory(vertices, sizeof(VertexColor) * MAX_DEBUG_LINE);


	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(VertexColor) * MAX_DEBUG_LINE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	D3DXMatrixIdentity(&world);
}

DebugLine::~DebugLine()
{
	SafeDelete(shader);

	SafeDeleteArray(vertices);
	SafeRelease(vertexBuffer);
}
