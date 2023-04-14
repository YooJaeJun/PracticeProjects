#include "CStaticMesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMesh::ACStaticMesh()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/MatineeCam_SM.MatineeCam_SM'");
	Mesh->SetStaticMesh(mesh);

	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'");
	Mesh->SetMaterial(0, Material);

#if WITH_EDITOR
	GLog->Log(GetActorLabel());
#endif
}

void ACStaticMesh::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
void ACStaticMesh::Paint()
{
	for (const FVectorParameterValue& value : Material->VectorParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("Color") == 0)
			Material->SetVectorParameterValueEditorOnly(value.ParameterInfo, FLinearColor::MakeRandomColor());
	}
}
#endif