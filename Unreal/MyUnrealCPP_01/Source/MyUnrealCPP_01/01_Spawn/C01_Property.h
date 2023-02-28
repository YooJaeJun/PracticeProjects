#pragma once

#include "CoreMinimal.h"	// 
#include "GameFramework/Actor.h"	// �θ�, �ʿ��� Ŭ����
#include "C01_Property.generated.h"	// �ڵ�����

UCLASS()	// ����ȭ
class MYUNREALCPP_01_API AC01_Property : public AActor	// Ŭ������ + API
{
	GENERATED_BODY()	// ����ȭ�ϱ� ���� ��ɵ��� ���ǵǾ� ����. UCLASS()�� ��

public:
	// ����ȭ ������. �ʱ�ȭ 0 �ڵ�
	UPROPERTY(EditAnywhere)	// 
		int A;
	UPROPERTY(EditDefaultsOnly)	// C���� ������ �� �״�� ���, Ŭ���� Ÿ�Կ� ������ ���� ����Ʈ�� ����
		int B;
	UPROPERTY(EditInstanceOnly)	// �ν��Ͻ� ���� �� ������ �� �ְ�
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
