#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_CameraAnim.generated.h"

UCLASS()
class MYUNREALCPP_04_API UCAnimNotifyState_CameraAnim : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCAnimNotifyState_CameraAnim();

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraAnim* CameraAnim;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float BlendInTime = 0;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float BlendOutTIme = 0;

	UPROPERTY(EditAnywhere, Category = "Camera")
		TSoftObjectPtr<class ACharacter> Target;

	UPROPERTY(EditAnywhere, Category = "Modifier")
		TSubclassOf<class UCCameraModifier> ModifierClass;

	UPROPERTY(EditAnywhere, Category = "Modifier")
		FVector LocationOffset = FVector(-400, 0, 90);

	UPROPERTY(EditAnywhere, Category = "Modifier")
		float PitchOffset = -15;

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	class UCCameraModifier* Modifier;
};
