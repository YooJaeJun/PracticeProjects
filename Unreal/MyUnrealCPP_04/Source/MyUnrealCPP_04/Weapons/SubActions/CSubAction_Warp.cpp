#include "Weapons/SubActions/CSubAction_Warp.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

UCSubAction_Warp::UCSubAction_Warp()
{
	CameraActorClass = ACameraActor::StaticClass();
}

void UCSubAction_Warp::BeginPlay(ACharacter* InOwner, ACAttachment* InAttachment, UCDoAction* InDoAction)
{
	Super::BeginPlay(InOwner, InAttachment, InDoAction);

	PlayerController = InOwner->GetController<APlayerController>();

	CameraActor = InOwner->GetWorld()->SpawnActor<ACameraActor>(CameraActorClass);
	CameraActor->SetActorRotation(FRotator(-90, 0, 0));


	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(CameraActor);
	camera->ProjectionMode = ProjectionMode;
	camera->OrthoWidth = OrthoWidth;
	camera->FieldOfView = FieldOfView;
}

void UCSubAction_Warp::Pressed()
{
	CheckNull(PlayerController);
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();


	State->OnSubActionMode();
	Movement->EnableTopViewCamera();
	PlayerController->SetViewTargetWithBlend(CameraActor, BlendIn);
}

void UCSubAction_Warp::Released()
{
	Super::Released();

	CheckNull(PlayerController);
	CheckFalse(State->IsSubActionMode());

	Super::Released();


	State->OffSubActionMode();
	Movement->DisableTopViewCamera();
	PlayerController->SetViewTargetWithBlend(Owner, BlendIn);
}

void UCSubAction_Warp::Tick_Implementation(float InDeltaTime)
{
	Super::Tick_Implementation(InDeltaTime);

	CheckNull(PlayerController);
	CheckNull(CameraActor);

	CameraActor->SetActorLocation(Owner->GetActorLocation() + CameraRelativeLocation);
}
