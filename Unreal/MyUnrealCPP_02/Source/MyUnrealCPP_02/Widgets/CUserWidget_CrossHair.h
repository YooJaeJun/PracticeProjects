#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_CrossHair.generated.h"

UCLASS()
class MYUNREALCPP_02_API UCUserWidget_CrossHair : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeOnInitialized() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void UpdateSpreadRange(float InRadius, float InMaxRadius);

private:
	TArray<class UBorder*> Borders;
	TArray<FVector2D> Alignments;

private:
	float Radius;
	float MaxRadius;

private:
	enum class EDirection
	{
		Top, Bottom, Left, Right, Max, 
	};
};
