#include "Framework.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator(Shader * shader)
	: shader(shader)
{
	model = new Model();

	tweenBuffer = new ConstantBuffer(&tweenDesc, sizeof(TweenDesc) * MAX_MODEL_INSTANCE);
	sTweenBuffer = shader->AsConstantBuffer("CB_TweenFrame");

	blendBuffer = new ConstantBuffer(&blendDesc, sizeof(BlendDesc) * MAX_MODEL_INSTANCE);
	sBlendBuffer = shader->AsConstantBuffer("CB_BlendFrame");

	instanceBuffer = new VertexBuffer(worlds, MAX_MODEL_INSTANCE, sizeof(Matrix), 1, true);


	//Create Compute Shader
	{
		computeShader = new Shader(L"71_GetMultiBones.fx");
		
		inputWorldBuffer = new StructuredBuffer(worlds, sizeof(Matrix), MAX_MODEL_INSTANCE);
		sInputWorldSRV = computeShader->AsSRV("InputWorlds");

		inputBoneBuffer = new StructuredBuffer(NULL, sizeof(Matrix), MAX_MODEL_TRANSFORMS);
		sInputBoneSRV = computeShader->AsSRV("InputBones");


		ID3D11Texture2D* texture;
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4;
		desc.Height = MAX_MODEL_INSTANCE;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;
		Check(D3D::GetDevice()->CreateTexture2D(&desc, NULL, &texture));

		outputBuffer = new TextureBuffer(texture);
		SafeRelease(texture);


		sOutputUAV = computeShader->AsUAV("Output");

		sTransformsSRV = computeShader->AsSRV("TransformsMap");
		sComputeTweenBuffer = computeShader->AsConstantBuffer("CB_TweenFrame");
		sComputeBlendBuffer = computeShader->AsConstantBuffer("CB_BlendFrame");

	}
}

ModelAnimator::~ModelAnimator()
{
	SafeDelete(model);

	SafeDeleteArray(clipTransforms);
	SafeRelease(texture);
	SafeRelease(srv);

	SafeDelete(tweenBuffer);
	SafeDelete(blendBuffer);

	SafeDelete(instanceBuffer);


	SafeDelete(computeShader);

	SafeDelete(inputWorldBuffer);
	SafeDelete(inputBoneBuffer);
	SafeDelete(outputBuffer);
}

void ModelAnimator::Update()
{
	if (texture == NULL)
	{
		for (ModelMesh* mesh : model->Meshes())
			mesh->SetShader(shader);

		CreateTexture();


		Matrix bones[MAX_MODEL_TRANSFORMS];
		for (UINT i = 0; i < model->BoneCount(); i++)
			bones[i] = model->BoneByIndex(i)->Transform();

		inputBoneBuffer->CopyToInput(bones);
	}

	for (UINT i = 0; i < transforms.size(); i++)
		blendDesc[i].Mode == 0 ? UpdateTweenMode(i) : UpdateBlendMode(i);

	
	
	tweenBuffer->Render();
	blendBuffer->Render();


	frameTime += Time::Delta();
	if (frameTime > (1.0f / frameRate))	// 정해진 프레임 지나갔으면
	{
		sComputeTweenBuffer->SetConstantBuffer(tweenBuffer->Buffer());
		sComputeBlendBuffer->SetConstantBuffer(blendBuffer->Buffer());

		sTransformsSRV->SetResource(srv);
		sInputWorldSRV->SetResource(inputWorldBuffer->SRV());
		sInputBoneSRV->SetResource(inputBoneBuffer->SRV());
		sOutputUAV->SetUnorderedAccessView(outputBuffer->UAV());

		computeShader->Dispatch(0, 0, 1, MAX_MODEL_INSTANCE, 1);

		outputBuffer->CopyFromOutput();
	}
	frameTime = fmod(frameTime, (1.0f / frameRate));


	if (Keyboard::Get()->Down(VK_SPACE))
	{
		ID3D11Texture2D* temp = outputBuffer->CopyFromOutput();

		FILE* src;
		fopen_s(&src, "../src.csv", "w");

		Matrix id[MAX_MODEL_TRANSFORMS];

		for (UINT y = 0; y < MAX_MODEL_INSTANCE; y++)
		{
			D3D11_MAPPED_SUBRESOURCE subResource;
			D3D::GetDC()->Map(temp, 0, D3D11_MAP_READ, 0, &subResource);
			{
				void* p = (BYTE *)subResource.pData + y * subResource.RowPitch;
				memcpy(id, p, MAX_MODEL_TRANSFORMS * sizeof(Matrix));
			}
			D3D::GetDC()->Unmap(temp, 0);


			for (UINT x = 0; x < MAX_MODEL_TRANSFORMS; x++)
			{
				Matrix destMatrix = id[x];

				fprintf(src, "%f,%f,%f,%f,", destMatrix._11, destMatrix._12, destMatrix._13, destMatrix._14);
				fprintf(src, "%f,%f,%f,%f,", destMatrix._21, destMatrix._22, destMatrix._23, destMatrix._24);
				fprintf(src, "%f,%f,%f,%f,", destMatrix._31, destMatrix._32, destMatrix._33, destMatrix._34);
				fprintf(src, "%f,%f,%f,%f\n", destMatrix._41, destMatrix._42, destMatrix._43, destMatrix._44);
			}
		}

		fclose(src);
	}


	for (ModelMesh* mesh : model->Meshes())
		mesh->Update();
}

void ModelAnimator::UpdateTweenMode(UINT index)
{
	TweenDesc& desc = tweenDesc[index];

	//현재 애니메이션
	{
		ModelClip* clip = model->ClipByIndex(desc.Curr.Clip);

		desc.Curr.RunningTime += Time::Delta();

		float time = 1.0f / clip->FrameRate() / desc.Curr.Speed;
		if (desc.Curr.Time >= 1.0f)
		{
			desc.Curr.RunningTime = 0;

			desc.Curr.CurrFrame = (desc.Curr.CurrFrame + 1) % clip->FrameCount();
			desc.Curr.NextFrame = (desc.Curr.CurrFrame + 1) % clip->FrameCount();
		}
		desc.Curr.Time = desc.Curr.RunningTime / time;
	}

	if (desc.Next.Clip > -1)
	{
		desc.ChangeTime += Time::Delta();
		desc.TweenTime = desc.ChangeTime / desc.TakeTime;

		if (desc.TweenTime >= 1.0f)
		{
			desc.Curr = desc.Next;

			desc.Next.Clip = -1;
			desc.Next.CurrFrame = 0;
			desc.Next.NextFrame = 0;
			desc.Next.Time = 0;
			desc.Next.RunningTime = 0.0f;

			desc.ChangeTime = 0.0f;
			desc.TweenTime = 0.0f;
		}
		else
		{
			ModelClip* clip = model->ClipByIndex(desc.Next.Clip);

			desc.Next.RunningTime += Time::Delta();

			float time = 1.0f / clip->FrameRate() / desc.Next.Speed;
			if (desc.Next.Time >= 1.0f)
			{
				desc.Next.RunningTime = 0;

				desc.Next.CurrFrame = (desc.Next.CurrFrame + 1) % clip->FrameCount();
				desc.Next.NextFrame = (desc.Next.CurrFrame + 1) % clip->FrameCount();
			}
			desc.Next.Time = desc.Next.RunningTime / time;
		}
	}
}

void ModelAnimator::UpdateBlendMode(UINT index)
{
	BlendDesc& desc = blendDesc[index];

	for (UINT i = 0; i < 3; i++)
	{
		ModelClip* clip = model->ClipByIndex(desc.Clip[i].Clip);

		desc.Clip[i].RunningTime += Time::Delta();

		float time = 1.0f / clip->FrameRate() / desc.Clip[i].Speed;
		if (desc.Clip[i].Time >= 1.0f)
		{
			desc.Clip[i].RunningTime = 0;

			desc.Clip[i].CurrFrame = (desc.Clip[i].CurrFrame + 1) % clip->FrameCount();
			desc.Clip[i].NextFrame = (desc.Clip[i].CurrFrame + 1) % clip->FrameCount();
		}
		desc.Clip[i].Time = desc.Clip[i].RunningTime / time;
	}
}

void ModelAnimator::Render()
{
	sTweenBuffer->SetConstantBuffer(tweenBuffer->Buffer());	
	sBlendBuffer->SetConstantBuffer(blendBuffer->Buffer());


	instanceBuffer->Render();

	for (ModelMesh* mesh : model->Meshes())
		mesh->Render(transforms.size());	
}

void ModelAnimator::ReadMesh(wstring file)
{
	model->ReadMesh(file);
}

void ModelAnimator::ReadMaterial(wstring file)
{
	model->ReadMaterial(file);
}

void ModelAnimator::ReadClip(wstring file)
{
	model->ReadClip(file);
}

void ModelAnimator::Pass(UINT pass)
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Pass(pass);
}

void ModelAnimator::PlayTweenMode(UINT index, UINT clip, float speed, float takeTime)
{
	blendDesc[index].Mode = 0;

	tweenDesc[index].TakeTime = takeTime;
	tweenDesc[index].Next.Clip = clip;
	tweenDesc[index].Next.Speed = speed;
}

void ModelAnimator::PlayBlendMode(UINT index, UINT clip, UINT clip1, UINT clip2)
{
	blendDesc[index].Mode = 1;

	blendDesc[index].Clip[0].Clip = clip;
	blendDesc[index].Clip[1].Clip = clip1;
	blendDesc[index].Clip[2].Clip = clip2;
}

void ModelAnimator::SetBlendAlpha(UINT index, float alpha)
{
	alpha = Math::Clamp(alpha, 0.0f, 2.0f);

	blendDesc[index].Alpha = alpha;
}

void ModelAnimator::GetAttachTransform(UINT instance, Matrix * outResult)
{
	ID3D11Texture2D* texture = outputBuffer->Result();

	D3D11_MAPPED_SUBRESOURCE subResource;
	D3D::GetDC()->Map(texture, 0, D3D11_MAP_READ, 0, &subResource);
	{
		memcpy(outResult, (BYTE *)subResource.pData + (instance * subResource.RowPitch), sizeof(Matrix) * MAX_MODEL_TRANSFORMS);
	}
	D3D::GetDC()->Unmap(texture, 0);
}

void ModelAnimator::CreateTexture()
{
	//Matrix matrix[MAX_MODEL_KEYFRAMES][MAX_MODEL_TRANSFORMS];

	clipTransforms = new ClipTransform[model->ClipCount()];
	for (UINT i = 0; i < model->ClipCount(); i++)	
		CreateClipTransform(i);
	

	//Create Texture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4;
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = model->ClipCount();
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //16Byte * 4 = 64Byte
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		UINT pageSize = MAX_MODEL_TRANSFORMS * 4 * 16 * MAX_MODEL_KEYFRAMES;
		//void* p = malloc(pageSize * model->ClipCount());
		void* p = VirtualAlloc(NULL, pageSize * model->ClipCount(), MEM_RESERVE, PAGE_READWRITE);

		//MEMORY_BASIC_INFORMATION, VirtualQuery

		for (UINT c = 0; c < model->ClipCount(); c++)
		{
			UINT start = c * pageSize;

			for (UINT k = 0; k < MAX_MODEL_KEYFRAMES; k++)
			{
				void* temp = (BYTE *)p + MAX_MODEL_TRANSFORMS * k * sizeof(Matrix) + start;

				VirtualAlloc(temp, MAX_MODEL_TRANSFORMS * sizeof(Matrix), MEM_COMMIT, PAGE_READWRITE);
				memcpy(temp, clipTransforms[c].Transform[k], MAX_MODEL_TRANSFORMS * sizeof(Matrix));
			}
		}//for(c)


		D3D11_SUBRESOURCE_DATA* subResources = new D3D11_SUBRESOURCE_DATA[model->ClipCount()];
		for (UINT c = 0; c < model->ClipCount(); c++)
		{
			void* temp = (BYTE *)p + c * pageSize;

			subResources[c].pSysMem = temp;
			subResources[c].SysMemPitch = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
			subResources[c].SysMemSlicePitch = pageSize;
		}
		Check(D3D::GetDevice()->CreateTexture2D(&desc, subResources, &texture));

		
		SafeDeleteArray(subResources);
		VirtualFree(p, 0, MEM_RELEASE);
	}


	//Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = model->ClipCount();

		Check(D3D::GetDevice()->CreateShaderResourceView(texture, &desc, &srv));
	}

	for (ModelMesh* mesh : model->Meshes())
		mesh->TransformsSRV(srv);
}

void ModelAnimator::CreateClipTransform(UINT index)
{
	Matrix* bones = new Matrix[MAX_MODEL_TRANSFORMS];

	ModelClip* clip = model->ClipByIndex(index);
	for (UINT f = 0; f < clip->FrameCount(); f++)
	{
		for (UINT b = 0; b < model->BoneCount(); b++)
		{
			ModelBone* bone = model->BoneByIndex(b);


			Matrix parent;
			Matrix invGlobal = bone->Transform();
			D3DXMatrixInverse(&invGlobal, NULL, &invGlobal);

			int parentIndex = bone->ParentIndex();
			if (parentIndex < 0)
				D3DXMatrixIdentity(&parent);
			else
				parent = bones[parentIndex];


			Matrix animation;
			ModelKeyframe* frame = clip->Keyframe(bone->Name());

			if (frame != NULL)
			{
				ModelKeyframeData& data = frame->Transforms[f];

				Matrix S, R, T;
				D3DXMatrixScaling(&S, data.Scale.x, data.Scale.y, data.Scale.z);
				D3DXMatrixRotationQuaternion(&R, &data.Rotation);
				D3DXMatrixTranslation(&T, data.Translation.x, data.Translation.y, data.Translation.z);

				animation = S * R * T;
			}
			else
			{
				D3DXMatrixIdentity(&animation);
			}

			bones[b] = animation * parent;
			clipTransforms[index].Transform[f][b] = invGlobal * bones[b];
		}//for(b)
	}//for(f)
}

Transform * ModelAnimator::AddTransform()
{
	Transform* transform = new Transform();
	transforms.push_back(transform);

	return transform;
}

void ModelAnimator::UpdateTransforms()
{
	for (UINT i = 0; i < transforms.size(); i++)
		memcpy(worlds[i], transforms[i]->World(), sizeof(Matrix));

	D3D11_MAPPED_SUBRESOURCE subResource;
	D3D::GetDC()->Map(instanceBuffer->Buffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, worlds, sizeof(Matrix) * MAX_MESH_INSTANCE);
	}
	D3D::GetDC()->Unmap(instanceBuffer->Buffer(), 0);

	inputWorldBuffer->CopyToInput(worlds);
}