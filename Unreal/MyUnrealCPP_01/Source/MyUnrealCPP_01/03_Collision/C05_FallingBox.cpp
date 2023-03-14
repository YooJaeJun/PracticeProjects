#include "03_Collision/C05_FallingBox.h"
#include "Global.h"
#include "C05_MultiTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

AC05_FallingBox::AC05_FallingBox()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Cube.Cube'");

	for (int32 i=0; i<3; i++)
	{
		FString str;
		str.Append("Meshes");
		str.Append(FString::FromInt(i + 1));

		CHelpers::CreateComponent<UStaticMeshComponent>(this, &Meshes[i], FName(str), Root);

		Meshes[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		Meshes[i]->SetStaticMesh(mesh);
		Meshes[i]->SetSimulatePhysics(true);
	}

	CreateTextRender();
}

void AC05_FallingBox::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/M_White_Inst.M_White_Inst'");

	for (int32 i = 0; i < 3; i++)
	{
		Materials[i] = UMaterialInstanceDynamic::Create(material, this);
		Materials[i]->SetVectorParameterValue("Color", FLinearColor::White);

		Meshes[i]->SetMaterial(0, Materials[i]);
		Meshes[i]->SetSimulatePhysics(false);

		FTransform transform = Meshes[i]->GetComponentToWorld();
		WorldLocation[i] = transform.GetLocation();
	}

	AC05_MultiTrigger* trigger = CHelpers::FindActor<AC05_MultiTrigger>(GetWorld());
	CheckNull(trigger);

	trigger->OnMultiLightOverlap.AddUFunction(this, "OnPhysics");
	trigger->OnMultiLightOverlap.Broadcast(0, FLinearColor::Red);
}

void AC05_FallingBox::OnPhysics(int32 InIndex, FLinearColor InColor)
{
	for (int32 i=0; i<3; i++)
	{
		Materials[i]->SetVectorParameterValue("Color", FLinearColor::White);
		Meshes[i]->SetSimulatePhysics(false);
		Meshes[i]->SetWorldLocation(WorldLocation[i]);
	}

	Materials[InIndex]->SetVectorParameterValue("Color", InColor);
	Meshes[InIndex]->SetSimulatePhysics(true);
}


