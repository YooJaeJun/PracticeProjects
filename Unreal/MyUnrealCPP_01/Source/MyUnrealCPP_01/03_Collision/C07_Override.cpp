#include "03_Collision/C07_Override.h"
#include "Global.h"
#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC07_Override::AC07_Override()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
}

void AC07_Override::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC07_Override::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC07_Override::OnEndOverlap);
}

void AC07_Override::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ChangeColorRed();
}

void AC07_Override::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ChangeColorWhite();
}

void AC07_Override::ChangeColorWhite_Implementation()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckNull(player);

	player->ChangeColor(FLinearColor::White);
}
