#include "04_Trace/C02_Cylinder.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

AC02_Cylinder::AC02_Cylinder()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Root);

	CreateTextRender();

	Text->SetRelativeLocation(FVector(0, 0, 150));


	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cylinder.Cylinder'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(1, 1, 2.5f));
}

void AC02_Cylinder::BeginPlay()
{
	Super::BeginPlay();
	
}

