#pragma once

#include "CoreMinimal.h"	// 
#include "GameFramework/Actor.h"	// 부모, 필요한 클래스
#include "C01_Property.generated.h"	// 자동생성

UCLASS()	// 직렬화
class MYUNREALCPP_01_API AC01_Property : public AActor	// 클래스명+API
{
	GENERATED_BODY()	// 직렬화하기 위한 기능들이 정의되어 있음. UCLASS()와 쌍

public:
	UPROPERTY(EditAnywhere)	// 직렬화 변수
		int a;
	UPROPERTY(EditDefaultsOnly)	// 직렬화 변수
		int b;
	UPROPERTY(EditInstanceOnly)	// 직렬화 변수
		int c;

public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
