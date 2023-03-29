#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class MYUNREALCPP_02_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		FVector2D PitchRange = FVector2D(-40, +40);

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Backpack;

private:
	UPROPERTY(VisibleAnywhere)
		class UCWeaponComponent* Weapon;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(const float InAxisValue);
	void OnMoveRight(const float InAxisValue);
	void OnHorizontalLook(const float InAxisValue);
	void OnVerticalLook(const float InAxisValue);

private:
	void OnRun();
	void OffRun();
};
