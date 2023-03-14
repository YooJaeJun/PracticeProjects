#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceResult, class AActor*, InActor, FLinearColor, InColor);

UCLASS()
class MYUNREALCPP_01_API AC02_LineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	AC02_LineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void StartLaunch(class AActor* InActor, FLinearColor InColor);

public:
	FLineTraceResult OnLineTraceResult;

private:
	TArray<class AC02_Cylinder*> Cylinders;
};
