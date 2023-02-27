#pragma once

#include "CoreMinimal.h"	// 
#include "GameFramework/Actor.h"	// �θ�, �ʿ��� Ŭ����
#include "C01_Property.generated.h"	// �ڵ�����

UCLASS()	// ����ȭ
class MYUNREALCPP_01_API AC01_Property : public AActor	// Ŭ������+API
{
	GENERATED_BODY()	// ����ȭ�ϱ� ���� ��ɵ��� ���ǵǾ� ����. UCLASS()�� ��

public:
	UPROPERTY(EditAnywhere)	// ����ȭ ����
		int a;
	UPROPERTY(EditDefaultsOnly)	// ����ȭ ����
		int b;
	UPROPERTY(EditInstanceOnly)	// ����ȭ ����
		int c;

public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
