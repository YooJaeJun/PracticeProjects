#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState.generated.h"

UCLASS()
class MYUNREALCPP_04_API UCAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraAnim* CameraAnim;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float BlendInTime = 0;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float BlendOutTIme = 0;
};
