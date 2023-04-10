#include "Framework.h"
#include "Billboard.h"

Billboard::Billboard(Shader* shader)
	: Renderer(shader)
{
	Topology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	
	sDiffuseMap = shader->AsSRV("BillboardMap");
}

Billboard::~Billboard()
{
	SafeDelete(textureArray);
}

void Billboard::Update()
{
	Super::Update();
}

void Billboard::Render()
{
	if (textureNames.size() > 0 && textureArray == NULL)
	{
		SafeDelete(textureArray);

		textureArray = new TextureArray(textureNames);
	}

	if (vertexCount != vertices.size())
	{
		vertexCount = vertices.size();

		SafeDelete(vertexBuffer);
		vertexBuffer = new VertexBuffer(&vertices[0], vertices.size(), sizeof(VertexBillboard));
	}

	Super::Render();


	sDiffuseMap->SetResource(textureArray->SRV());
	shader->Draw(0, Pass(), vertexCount);
}

void Billboard::AddTexture(wstring file)
{
	textureNames.push_back(file);
}

void Billboard::Add(Vector3 & position, Vector2 & scale, UINT mapIndex)
{
	VertexBillboard vertex = 
	{
		position, scale, mapIndex
	};

	vertices.push_back(vertex);
}
