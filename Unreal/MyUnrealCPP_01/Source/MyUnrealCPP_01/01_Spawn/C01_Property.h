#pragma once

#include "CoreMinimal.h"	// 
#include "GameFramework/Actor.h"	// 부모, 필요한 클래스
#include "C01_Property.generated.h"	// 자동생성

UCLASS()	// 직렬화
class MYUNREALCPP_01_API AC01_Property : public AActor	// 클래스명 + API
{
	GENERATED_BODY()	// 직렬화하기 위한 기능들이 정의되어 있음. UCLASS()와 쌍

public:
	// 직렬화 변수들. 초기화 0 자동
	UPROPERTY(EditAnywhere)	// 
		int A;
	UPROPERTY(EditDefaultsOnly)	// C에서 지정한 것 그대로 사용, 클래스 타입에 지정한 것은 디폴트로 공유
		int B;
	UPROPERTY(EditInstanceOnly)	// 인스턴스 각각 값 변경할 수 있게
		int C;

	UPROPERTY(VisibleAnywhere, Category = "Property")
		float D;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Property")
		int Variable = 10;

public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
