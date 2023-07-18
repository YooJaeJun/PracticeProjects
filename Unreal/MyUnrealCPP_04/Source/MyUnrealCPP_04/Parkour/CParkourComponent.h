#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DataTable.h"
#include "CParkourComponent.generated.h"

UENUM(BlueprintType)
enum class EParkourArrowType : uint8
{
    Center = 0, Ceil, Floor, Left, Right, Land, Max,
};

UENUM(BlueprintType)
enum class EParkourType : uint8
{
    Climb = 0, Fall, Slide, Short, Normal, Wall, Max,
};

USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
        EParkourType Type;

    UPROPERTY(EditAnywhere)
        UAnimMontage* Montage;

    UPROPERTY(EditAnywhere)
        float PlayRatio = 1.f;

    UPROPERTY(EditAnywhere)
        FName SectionName;

    UPROPERTY(EditAnywhere)
        float MinDistance;

    UPROPERTY(EditAnywhere)
        float MaxDistance;

    UPROPERTY(EditAnywhere)
        float Extent;

    UPROPERTY(EditAnywhere)
        bool bFixedCamera;

public:
    void PlayMontage(class ACharacter* InCharacter);
};

// 블루프린트 활당됨
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
UCLASS()
class MYUNREALCPP_04_API UCParkourComponent : public UActorComponent
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Data")
        UDataTable* DataTable;
    
private:
    UPROPERTY(EditAnywhere, Category = "Trace")
        float TraceDistance = 600;

    UPROPERTY(EditAnywhere, Category = "Trace")
        TEnumAsByte<EDrawDebugTrace::Type> DebugType;

    UPROPERTY(EditAnywhere, Category = "Trace")
        float AvailableFrontAngle = 15;

public:	
	UCParkourComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void LineTrace(EParkourArrowType InType);

private:
    void CheckTrace_Center();

private:
    TMap<EParkourType, TArray<FParkourData>> DataMap;

private:
    class ACharacter* OwnerCharacter;
    class UArrowComponent* Arrows[(int32)EParkourArrowType::Max];

    FHitResult HitResults[(int32)EParkourArrowType::Max];
    
private:
    AActor* HitObstacle;
    FVector HitObstacleExtent;
    float HitDistance;
    float ToFrontYaw;
};
