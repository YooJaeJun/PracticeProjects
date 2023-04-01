#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "CAnimInstance_Arms.h"
#include "Weapons/CWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Backpack, "Backpack", GetMesh(), "Backpack");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Arms, "Arms", Camera);

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

	UStaticMesh* staticMesh;
	CHelpers::GetAsset<UStaticMesh>(&staticMesh, "StaticMesh'/Game/FPS_Weapon_Bundle/Backpack/Backpack.Backpack'");
	Backpack->SetStaticMesh(staticMesh);
	Backpack->SetCollisionProfileName("NoCollision");

	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character_Arms/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'");
	Arms->SetSkeletalMesh(mesh);
	Arms->SetRelativeLocation(FVector(-14.25f, -5.85f, -156.935f));
	Arms->SetRelativeRotation(FRotator(-0.5f, -11.85f, -1.2f));
	Arms->SetVisibility(false);

	TSubclassOf<UCAnimInstance_Arms> armsAnimInstance;
	CHelpers::GetClass<UCAnimInstance_Arms>(&armsAnimInstance, "AnimBlueprint'/Game/Player/ABP_Player_Arms.ABP_Player_Arms_C'");
	Arms->SetAnimClass(armsAnimInstance);
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
	PlayerInputComponent->BindAction("AK47", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::SetAK47Mode);
	PlayerInputComponent->BindAction("Pistol", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::SetPistolMode);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Begin_Aim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::End_Aim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Begin_Fire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, Weapon, &UCWeaponComponent::End_Fire);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::ToggleAutoFire);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, Weapon, &UCWeaponComponent::Reload);
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

