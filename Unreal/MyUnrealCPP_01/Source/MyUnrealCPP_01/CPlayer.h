#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class MYUNREALCPP_01_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

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

public:
	UFUNCTION(BlueprintCallable, Category = "Color")
		void ChangeColor(FLinearColor InColor);

private:
	TArray<class UMaterialInstanceDynamic*> Materials;
};
