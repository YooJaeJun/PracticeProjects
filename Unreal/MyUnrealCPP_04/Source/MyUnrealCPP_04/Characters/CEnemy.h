#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class MYUNREALCPP_04_API ACEnemy
	: public ACharacter
	, public IICharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor OriginColor = FLinearColor::White;

	UPROPERTY(VisibleAnywhere)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleAnywhere)
		class UCMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere)
		class UCStateComponent* State;

	UPROPERTY(VisibleAnywhere)
		class UCStatusComponent* Status;

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

protected:
	virtual void Hitted();

public:
	virtual void End_Hitted() override;

private:
	void Dead();

public:
	void End_Dead() override;

private:
	UFUNCTION()
		void RestoreColor();

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	struct FDamageData
	{
		float Power;
		class ACharacter* Character;
		class AActor* Causer;

		const struct FActionDamageEvent* Event;
	} Damage;

private:
	FTimerHandle RestoreColor_TimerHandle;
};
