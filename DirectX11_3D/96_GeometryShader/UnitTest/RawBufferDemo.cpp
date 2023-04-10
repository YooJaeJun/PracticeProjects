#include "stdafx.h"
#include "RawBufferDemo.h"

void RawBufferDemo::Initialize()
{
	Shader* shader = new Shader(L"60_RawBuffer.fx");


	UINT count = 2 * 10 * 8 * 3;

	struct Output
	{
		UINT GroupID[3];
		UINT GroupThreadID[3];
		UINT DispatchThreadID[3];
		UINT GroupIndex;
		float RetValue;
	};
	//RawBuffer* rawBuffer = new RawBuffer(NULL, 0, sizeof(Output) * count);

	struct Input
	{
		float Value = 0.0f;
	};
	Input* input = new Input[count];

	for (UINT i = 0; i < count; i++)
		input[i].Value = Math::Random(0.0f, 10000.0f);

	RawBuffer* rawBuffer = new RawBuffer(input, sizeof(Input) * count, sizeof(Output) * count);


	shader->AsSRV("Input")->SetResource(rawBuffer->SRV());
	shader->AsUAV("Output")->SetUnorderedAccessView(rawBuffer->UAV());
	shader->Dispatch(0, 0, 2, 1, 1);


	Output* output = new Output[count];
	rawBuffer->CopyFromOuput(output);

	FILE* file;
	fopen_s(&file, "../Raw.csv", "w");

	for (UINT i = 0; i < count; i++)
	{
		Output temp = output[i];

		fprintf
		(
			file,
			"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f\n",
			i,
			temp.GroupID[0], temp.GroupID[1], temp.GroupID[2],
			temp.GroupThreadID[0], temp.GroupThreadID[1], temp.GroupThreadID[2],
			temp.DispatchThreadID[0], temp.DispatchThreadID[1], temp.DispatchThreadID[2],
			temp.GroupIndex, temp.RetValue
		);
	}
	fclose(file);
}

void RawBufferDemo::Update()
{
	
}

void RawBufferDemo::Render()
{
	
}