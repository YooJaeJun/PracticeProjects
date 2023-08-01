#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "Parkour/CParkourComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class MYUNREALCPP_04_API ACPlayer
	: public ACharacter
	, public IICharacter
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 TeamID = 1;

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleAnywhere)
		class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleAnywhere)
		class UCMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCParkourComponent* Parkour;

	UPROPERTY(VisibleDefaultsOnly)
		class UCZoomComponent* Zoom;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* ArrowGroup;

	UPROPERTY(VisibleDefaultsOnly)
		class UArrowComponent* Arrows[(int32)EParkourArrowType::Max];
public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void OnAvoid();

private:
	void BackStep();

public:
	void End_BackStep() override;

public:
	void OnRightButton();
	void OffRightButton();

public:
	void Landed(const FHitResult& Hit) override;

private:
	void SetZooming(float InValue);
};
