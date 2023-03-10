#include "03_Collision/C02_ComponentOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


AC02_ComponentOverlap::AC02_ComponentOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->bHiddenInGame = false;
	Box->SetRelativeScale3D(FVector(3));
}

void AC02_ComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC02_ComponentOverlap::OnComponentEndOverlap);
}

void AC02_ComponentOverlap::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString str;

	str = "-----Begin-----";
	CLog::Log(str);

	str = FString::Printf(L"Overlap Component : %s", *OverlappedComponent->GetName());
	CLog::Log(str);

	str = FString::Printf(L"Other Actor : %s", *OtherActor->GetName());
	CLog::Log(str);

	str = FString::Printf(L"Other Component : %s", *OtherComp->GetName());
	CLog::Log(str);
}

void AC02_ComponentOverlap::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FString str;

	str = "-----End-----";
	CLog::Log(str);

	str = FString::Printf(L"Overlap Component : %s", *OverlappedComponent->GetName());
	CLog::Log(str);

	str = FString::Printf(L"Other Actor : %s", *OtherActor->GetName());
	CLog::Log(str);

	str = FString::Printf(L"Other Component : %s", *OtherComp->GetName());
	CLog::Log(str);
}

