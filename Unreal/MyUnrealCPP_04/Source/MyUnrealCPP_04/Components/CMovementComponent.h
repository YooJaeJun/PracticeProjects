#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CMovementComponent.generated.h"

UENUM()
enum class ESpeedType : uint8
{
	Walk = 0, Run, Sprint, Max,
};

UCLASS()
class MYUNREALCPP_04_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
		float HorizontalLook = 45;

	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
		float VerticalLook = 45;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 200, 400, 600 };

public:
	FORCEINLINE bool CanMove() { return bCanMove; }
	FORCEINLINE void Move() { bCanMove = true; }
	FORCEINLINE void Stop() { bCanMove = false; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESpeedType::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ESpeedType::Sprint]; }

	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

	FORCEINLINE void EnableTopViewCamera() { bTopViewCamera = true; }
	FORCEINLINE void DisableTopViewCamera() { bTopViewCamera = false; }

public:	
	UCMovementComponent();

protected:
	virtual void BeginPlay() override;

private:
	void SetSpeed(ESpeedType InType);

public:
	void OnSprint();
	void OnRun();
	void OnWalk();

	void EnableControlRotation();
	void DisableControlRotation();

public:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	class ACharacter* OwnerCharacter;

private:
	bool bCanMove = true;
	bool bFixedCamera;
	bool bTopViewCamera;
};
