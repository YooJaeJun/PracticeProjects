#include "Framework.h"
#include "PerFrame.h"

PerFrame::PerFrame(Shader * shader)
	: shader(shader)
{
	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_PerFrame");

	lightBuffer = new ConstantBuffer(&lightDesc, sizeof(LightDesc));
	sLightBuffer = shader->AsConstantBuffer("CB_Light");
}

PerFrame::~PerFrame()
{
	SafeDelete(buffer);
	SafeDelete(lightBuffer);
}

void PerFrame::Update()
{
	desc.Time = Time::Get()->Running();

	lightDesc.Ambient = Context::Get()->Ambient();
	lightDesc.Specular = Context::Get()->Specular();
	lightDesc.Direction = Context::Get()->Direction();
	lightDesc.Position = Context::Get()->Position();
}

void PerFrame::Render()
{
	desc.View = Context::Get()->View();
	D3DXMatrixInverse(&desc.ViewInverse, NULL, &desc.View);

	desc.Projection = Context::Get()->Projection();
	desc.VP = desc.View * desc.Projection;

	buffer->Render();
	sBuffer->SetConstantBuffer(buffer->Buffer());

	lightBuffer->Render();
	sLightBuffer->SetConstantBuffer(lightBuffer->Buffer());
}
