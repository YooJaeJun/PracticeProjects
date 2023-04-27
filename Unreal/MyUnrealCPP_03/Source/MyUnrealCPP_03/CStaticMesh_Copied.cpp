#include "CStaticMesh_Copied.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMesh_Copied::ACStaticMesh_Copied()
{
	bRunConstructionScriptOnDrag = false;

	CHelpers::CreateComponent(this, &Mesh, "Mesh");

	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'");
	Mesh->SetMaterial(0, Material);
}

void ACStaticMesh_Copied::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Mesh->CreateMeshSection(0, Positions, Indices, Normals, Uvs, Colors, TArray<FProcMeshTangent>(), true);
}

void ACStaticMesh_Copied::BeginPlay()
{
	Super::BeginPlay();
}
