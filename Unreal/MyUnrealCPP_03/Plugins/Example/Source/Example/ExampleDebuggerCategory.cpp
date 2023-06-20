#include "ExampleDebuggerCategory.h"
#include "DrawDebugHelpers.h"
#include "CanvasItem.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;
}

FExampleDebuggerCategory::~FExampleDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FExampleDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FExampleDebuggerCategory());
}

void FExampleDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	//GLog->Log(OwnerPC->GetPawn()->GetName());

	//if (!!DebugActor)
	//	GLog->Log(DebugActor->GetName());

	ACharacter* player = OwnerPC->GetPawn<ACharacter>();
	if (player == nullptr) 
		return;

	//Player
	{
		PlayerPawnData.bDraw = true;
		PlayerPawnData.Name = player->GetName();
		PlayerPawnData.Location = player->GetActorLocation();
		PlayerPawnData.Forward = player->GetActorForwardVector();
	}

	// Forward Actor
	{
		FHitResult hitResult;

		FVector start = PlayerPawnData.Location;
		FVector end = start + player->GetActorForwardVector() * TraceDistance;

		FCollisionQueryParams params;
		params.AddIgnoredActor(player); 

		player->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, params);

		if (hitResult.bBlockingHit)
		{
			ForwardActorData.bDraw = true;
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}
	}

	if (!!DebugActor)
	{
		DebugActorData.bDraw = true;
		DebugActorData.Name = DebugActor->GetName();
		DebugActorData.Location = DebugActor->GetActorLocation();
		DebugActorData.Forward = DebugActor->GetActorForwardVector();
	}
}

void FExampleDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FVector start = PlayerPawnData.Location;
	FVector end = start + PlayerPawnData.Forward * TraceDistance;

	DrawDebugLine(OwnerPC->GetWorld(), start, end, FColor::Red);

	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.25f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, L"  -- Player Pawn --");
	CanvasContext.Printf(FColor::White, L"  Name : %s", *PlayerPawnData.Name);
	CanvasContext.Printf(FColor::White, L"  Location : %s", *PlayerPawnData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"  Forward : %s", *PlayerPawnData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	if (ForwardActorData.bDraw)
	{
		CanvasContext.Printf(FColor::Green, L"  -- Forward Actor --");
		CanvasContext.Printf(FColor::White, L"  Name : %s", *ForwardActorData.Name);
		CanvasContext.Printf(FColor::White, L"  Location : %s", *ForwardActorData.Location.ToString());
		CanvasContext.Printf(FColor::White, L"  Forward : %s", *ForwardActorData.Forward.ToString());
		CanvasContext.Printf(FColor::White, L"");
	}

	if (DebugActorData.bDraw)
	{
		CanvasContext.Printf(FColor::Green, L"  -- Select Actor --");
		CanvasContext.Printf(FColor::White, L"  Name : %s", *DebugActorData.Name);
		CanvasContext.Printf(FColor::White, L"  Location : %s", *DebugActorData.Location.ToString());
		CanvasContext.Printf(FColor::White, L"  Forward : %s", *DebugActorData.Forward.ToString());
	}
}
