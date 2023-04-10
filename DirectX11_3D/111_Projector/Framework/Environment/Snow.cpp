#include "Framework.h"
#include "Snow.h"

Snow::Snow(Vector3 & extent, UINT count, wstring file)
	: Renderer(L"85_Snow.fxo"), drawCount(count)
{
	desc.Extent = extent;
	desc.DrawDistance = desc.Extent.z * 2.0f;

	texture = new Texture(file);
	shader->AsSRV("DiffuseMap")->SetResource(texture->SRV());

	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Snow");


	vertices = new VertexSnow[drawCount * 4];
	for (UINT i = 0; i < drawCount * 4; i += 4)
	{
		float scale;
		scale = Math::Random(0.1f, 0.4f);

		Vector3 position;
		position.x = Math::Random(-desc.Extent.x, desc.Extent.x);
		position.y = Math::Random(-desc.Extent.y, desc.Extent.y);
		position.z = Math::Random(-desc.Extent.z, desc.Extent.z);

		Vector2 random = Math::RandomVec2(0.0f, 1.0f);

		
		vertices[i + 0].Position = position;
		vertices[i + 1].Position = position;
		vertices[i + 2].Position = position;
		vertices[i + 3].Position = position;

		vertices[i + 0].Uv = Vector2(0, 1);
		vertices[i + 1].Uv = Vector2(0, 0);
		vertices[i + 2].Uv = Vector2(1, 1);
		vertices[i + 3].Uv = Vector2(1, 0);

		vertices[i + 0].Scale = scale;
		vertices[i + 1].Scale = scale;
		vertices[i + 2].Scale = scale;
		vertices[i + 3].Scale = scale;

		vertices[i + 0].Random = random;
		vertices[i + 1].Random = random;
		vertices[i + 2].Random = random;
		vertices[i + 3].Random = random;
	}

	indices = new UINT[drawCount * 6];
	for (UINT i = 0; i < drawCount; i++)
	{
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 2;
		indices[i * 6 + 4] = i * 4 + 1;
		indices[i * 6 + 5] = i * 4 + 3;
	}

	vertexBuffer = new VertexBuffer(vertices, drawCount * 4, sizeof(VertexSnow));
	indexBuffer = new IndexBuffer(indices, drawCount * 6);

	//ID3D11BlendState
	//D3D11_BLEND_DESC;
}

Snow::~Snow()
{
	SafeDelete(buffer);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeDelete(texture);
}

void Snow::Update()
{
	Super::Update();

	Context::Get()->GetCamera()->Position(&desc.Origin);
	//ImGui::SliderFloat3("Origin", desc.Origin, 0, 200);

	ImGui::SliderFloat3("Velocity", desc.Velocity, -200, 200);
	ImGui::ColorEdit3("Color", desc.Color);
	ImGui::SliderFloat("Distance", &desc.DrawDistance, 0, desc.Extent.z * 2.0f);
	ImGui::InputFloat("Turbulence", &desc.Turbulence, 0.1f);
}

void Snow::Render()
{
	Super::Render();

	buffer->Render();
	sBuffer->SetConstantBuffer(buffer->Buffer());


	static UINT pass = 0;
	ImGui::InputInt("Snow Pass", (int *)&pass);
	pass %= 4;
	
	shader->DrawIndexed(0, pass, drawCount * 6);
}
