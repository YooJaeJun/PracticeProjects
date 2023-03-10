#include "03_Collision/C03_OverlapAndHit.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC03_OverlapAndHit::AC03_OverlapAndHit()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->bHiddenInGame = false;
	Box->SetRelativeScale3D(FVector(3));
}

void AC03_OverlapAndHit::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC03_OverlapAndHit::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC03_OverlapAndHit::OnComponentEndOverlap);
	Box->OnComponentHit.AddDynamic(this, &AC03_OverlapAndHit::OnComponentHit);
}

void AC03_OverlapAndHit::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString str;

	str = FString::Printf(L"Begin Overlap : %s", *OtherActor->GetName());
	CLog::Log(str);
}

void AC03_OverlapAndHit::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FString str;

	str = FString::Printf(L"End Overlap : %s", *OtherActor->GetName());
	CLog::Log(str);
}

void AC03_OverlapAndHit::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString str;

	str = FString::Printf(L"Hit : %s", *OtherActor->GetName());
	CLog::Log(str);
}

