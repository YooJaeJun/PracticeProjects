#include "Framework.h"
#include "ParticleSystem.h"
#include "Utilities/Xml.h"

ParticleSystem::ParticleSystem(wstring file)
	: Renderer(L"89_Particle.fxo")
{
	ReadFile(L"../../_Textures/Particles/" + file + L".xml");

	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Particle");

	sMap = shader->AsSRV("ParticleMap");

	Reset();
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::Reset()
{
	currentTime = 0.0f;
	lastAddTime = Time::Get()->Running();
	gpuCount = leadCount = activeCount = deactiveCount = 0;


	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	vertices = new VertexParticle[data.MaxParticles * 4];
	for (UINT i = 0; i < data.MaxParticles; i++)
	{
		vertices[i * 4 + 0].Corner = Vector2(-1, -1);
		vertices[i * 4 + 1].Corner = Vector2(-1, +1);
		vertices[i * 4 + 2].Corner = Vector2(+1, -1);
		vertices[i * 4 + 3].Corner = Vector2(+1, +1);
	}

	indices = new UINT[data.MaxParticles * 6];
	for (UINT i = 0; i < data.MaxParticles; i++)
	{
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 2;
		indices[i * 6 + 4] = i * 4 + 1;
		indices[i * 6 + 5] = i * 4 + 3;
	}

	vertexBuffer = new VertexBuffer(vertices, data.MaxParticles * 4, sizeof(VertexParticle), 0, true);
	indexBuffer = new IndexBuffer(indices, data.MaxParticles * 6);
}

void ParticleSystem::Add(Vector3 & position)
{
	if (Time::Get()->Running() - lastAddTime < 60.0f / 1000.0f)
		return;

	lastAddTime = Time::Get()->Running();


	UINT count = leadCount + 1;

	if (count >= data.MaxParticles)
	{
		if (data.bLoop == true)
		{
			count = 0;
		}
		else
		{
			count = data.MaxParticles;

			return;
		}
	}
		

	if (count == deactiveCount)
		return;


	Vector3 velocity = Vector3(1, 1, 1);
	velocity *= data.StartVelocity;

	float horizontalVelocity = Math::Lerp(data.MinHorizontalVelocity, data.MaxHorizontalVelocity, Math::Random(0.0f, 1.0f));
	float horizontalAngle = Math::PI * 2.0f * Math::Random(0.0f, 1.0f);

	velocity.x += horizontalVelocity * cosf(horizontalAngle);
	velocity.y += horizontalVelocity * sinf(horizontalAngle);
	velocity.z += Math::Lerp(data.MinHorizontalVelocity, data.MaxHorizontalVelocity, Math::Random(0.0f, 1.0f));


	Vector4 random = Math::RandomVec4(0.0f, 1.0f);

	for (UINT i = 0; i < 4; i++)
	{
		vertices[leadCount * 4 + i].Position = position;
		vertices[leadCount * 4 + i].Velocity = velocity;
		vertices[leadCount * 4 + i].Random = random;
		vertices[leadCount * 4 + i].Time = currentTime;
	}

	leadCount = count;
}

void ParticleSystem::Update()
{
	Super::Update();

	currentTime += Time::Delta();

	MapVertices();
	Activate();
	Deactivate();

	if (activeCount == leadCount)
		currentTime = 0.0f;


	desc.MinColor = data.MinColor;
	desc.MaxColor = data.MaxColor;
	desc.ColorAmount = data.ColorAmount;

	desc.Gravity = data.Gravity;
	desc.EndVelocity = data.EndVelocity;

	desc.RotateSpeed = Vector2(data.MinRotateSpeed, data.MaxRotateSpeed);
	desc.StartSize = Vector2(data.MinStartSize, data.MaxStartSize);
	desc.EndSize = Vector2(data.MinEndSize, data.MaxEndSize);

	desc.ReadyTime = data.ReadyTime;
	desc.ReadyRandomTime = data.ReadyRandomTime;
}

void ParticleSystem::MapVertices()
{
	if (gpuCount == leadCount) return;

	D3D11_MAPPED_SUBRESOURCE subResource;

	if (leadCount > gpuCount)
	{
		D3D::GetDC()->Map(vertexBuffer->Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subResource);
		{
			UINT start = gpuCount * 4;
			UINT size = (leadCount - gpuCount) * sizeof(VertexParticle) * 4;
			UINT offset = gpuCount * sizeof(VertexParticle) * 4;

			BYTE* p = (BYTE *)subResource.pData + offset;
			memcpy(p, vertices + start, size);
		}
		D3D::GetDC()->Unmap(vertexBuffer->Buffer(), 0);
	}
	else
	{
		D3D::GetDC()->Map(vertexBuffer->Buffer(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subResource);
		{
			UINT start = gpuCount * 4;
			UINT size = (data.MaxParticles - gpuCount) * sizeof(VertexParticle) * 4;
			UINT offset = gpuCount * sizeof(VertexParticle) * 4;

			BYTE* p = (BYTE *)subResource.pData + offset;
			memcpy(p, vertices + start, size);
		}

		if (leadCount > 0)
		{
			UINT size = leadCount * sizeof(VertexParticle) * 4;

			memcpy(subResource.pData, vertices, size);
		}

		D3D::GetDC()->Unmap(vertexBuffer->Buffer(), 0);
	}

	gpuCount = leadCount;
}

void ParticleSystem::Activate()
{
	while (activeCount != gpuCount)
	{
		float age = currentTime - vertices[activeCount * 4].Time;

		if (age < data.ReadyTime)
			return;

		vertices[activeCount * 4].Time = currentTime;
		activeCount++;

		if (activeCount >= data.MaxParticles)
			activeCount = (data.bLoop == true) ? 0 : data.MaxParticles;
	}
}

void ParticleSystem::Deactivate()
{
	while (activeCount != deactiveCount)
	{
		float age = currentTime - vertices[deactiveCount * 4].Time;

		if (age > data.ReadyTime)
			return;

		deactiveCount++;

		if (deactiveCount >= data.MaxParticles)
			deactiveCount = (data.bLoop == true) ? 0 : data.MaxParticles;
	}
}

void ParticleSystem::Render()
{
	Super::Render();


	desc.CurrentTime = currentTime;

	buffer->Render();
	sBuffer->SetConstantBuffer(buffer->Buffer());

	sMap->SetResource(map->SRV());

	if (leadCount == activeCount) 
		return;


	UINT pass = (UINT)data.Type;
	if (leadCount > activeCount)
	{
		shader->DrawIndexed(0, pass, (leadCount - activeCount) * 6, activeCount * 6);
	}
	else
	{
		shader->DrawIndexed(0, pass, (data.MaxParticles - activeCount) * 6, activeCount * 6);

		if (leadCount > 0)
			shader->DrawIndexed(0, pass, leadCount * 6);
	}
}

void ParticleSystem::ReadFile(wstring file)
{
	Xml::XMLDocument* document = new Xml::XMLDocument();
	Xml::XMLError error = document->LoadFile(String::ToString(file).c_str());
	assert(error == Xml::XML_SUCCESS);

	Xml::XMLElement* root = document->FirstChildElement();

	Xml::XMLElement* node = root->FirstChildElement();
	data.Type = (ParticleData::BlendType)node->IntText();

	node = node->NextSiblingElement();
	data.bLoop = node->BoolText();

	node = node->NextSiblingElement();
	wstring textureFile = String::ToWString(node->GetText());
	data.TextureFile = L"Particles/" + textureFile;
	map = new Texture(data.TextureFile);


	node = node->NextSiblingElement();
	data.MaxParticles = node->IntText();

	node = node->NextSiblingElement();
	data.ReadyTime = node->FloatText();

	node = node->NextSiblingElement();
	data.ReadyRandomTime = node->FloatText();

	node = node->NextSiblingElement();
	data.StartVelocity = node->FloatText();

	node = node->NextSiblingElement();
	data.EndVelocity = node->FloatText();

	node = node->NextSiblingElement();
	data.MinHorizontalVelocity = node->FloatText();

	node = node->NextSiblingElement();
	data.MaxHorizontalVelocity = node->FloatText();

	node = node->NextSiblingElement();
	data.MinVerticalVelocity = node->FloatText();

	node = node->NextSiblingElement();
	data.MaxVerticalVelocity = node->FloatText();

	node = node->NextSiblingElement();
	data.Gravity.x = node->FloatAttribute("X");
	data.Gravity.y = node->FloatAttribute("Y");
	data.Gravity.z = node->FloatAttribute("Z");

	node = node->NextSiblingElement();
	data.ColorAmount = node->FloatText();

	node = node->NextSiblingElement();
	data.MinColor.r = node->FloatAttribute("R");
	data.MinColor.b = node->FloatAttribute("G");
	data.MinColor.g = node->FloatAttribute("B");
	data.MinColor.a = node->FloatAttribute("A");

	node = node->NextSiblingElement();
	data.MaxColor.r = node->FloatAttribute("R");
	data.MaxColor.b = node->FloatAttribute("G");
	data.MaxColor.g = node->FloatAttribute("B");
	data.MaxColor.a = node->FloatAttribute("A");

	node = node->NextSiblingElement();
	data.MinRotateSpeed = node->FloatText();

	node = node->NextSiblingElement();
	data.MaxRotateSpeed = node->FloatText();

	node = node->NextSiblingElement();
	data.MinStartSize = node->FloatText();

	node = node->NextSiblingElement();
	data.MaxStartSize = node->FloatText();

	node = node->NextSiblingElement();
	data.MinEndSize = node->FloatText();

	node = node->NextSiblingElement();
	data.MaxEndSize = node->FloatText();

	SafeDelete(document);
}
