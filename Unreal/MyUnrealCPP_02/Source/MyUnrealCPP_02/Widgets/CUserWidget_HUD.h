#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_HUD.generated.h"

UCLASS()
class MYUNREALCPP_02_API UCUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnAutoFire();

	UFUNCTION(BlueprintImplementableEvent)
		void OffAutoFire();
};
