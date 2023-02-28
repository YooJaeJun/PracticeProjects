#include "01_Spawn/C02_Mesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

AC02_Mesh::AC02_Mesh()
{
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//RootComponent = Mesh;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshes/Cube.Cube'");
	//if (mesh.Succeeded())
	//	Mesh->SetStaticMesh(mesh.Object);

	UStaticMesh* mesh = nullptr;
	CHelpers::GetAsset<UStaticMesh>(&mesh, TEXT("StaticMesh'/Game/Meshes/Cube.Cube'"));
	Mesh->SetStaticMesh(mesh);
}

void AC02_Mesh::BeginPlay()
{
	Super::BeginPlay();
	
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, L"MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	UMaterialInstanceConstant* material = nullptr;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'");

	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "SetRandomColor", 1, true);
}

void AC02_Mesh::SetRandomColor()
{
	Material->SetVectorParameterValue("Color", FLinearColor::MakeRandomColor());
}

