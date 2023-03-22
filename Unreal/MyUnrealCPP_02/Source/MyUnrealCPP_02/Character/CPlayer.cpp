#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Weapons/CWeaponComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'");
	GetMesh()->SetAnimClass(animInstance);


	// bUseControllerRotationYaw = false;
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400;


	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMin = PitchRange.X;
	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMax = PitchRange.Y;
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

	PlayerInputComponent->BindAction("AR4", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::SetAR4Mode);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Begin_Aim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::End_Aim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Begin_Fire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::End_Fire);
}

void ACPlayer::OnMoveForward(const float InAxisValue)
{
	const FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxisValue);
}

void ACPlayer::OnMoveRight(const float InAxisValue)
{
	const FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxisValue);
}

void ACPlayer::OnHorizontalLook(const float InAxisValue)
{
	AddControllerYawInput(InAxisValue);
}

void ACPlayer::OnVerticalLook(const float InAxisValue)
{
	AddControllerPitchInput(InAxisValue);
}

void ACPlayer::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

