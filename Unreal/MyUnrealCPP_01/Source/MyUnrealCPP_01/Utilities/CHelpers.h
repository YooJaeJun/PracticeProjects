#pragma once

#include "CoreMinimal.h"
#define CheckTrue(x) { if (x == true) return; }
#define CheckTrueResult(x, y) { if (x == true) return y; }

#define CheckFalse(x) { if(x == false) return;}
#define CheckFalseResult(x, y) { if(x == false) return y;}

#define CheckNull(x) { if(x == nullptr) return;}
#define CheckNullResult(x, y) { if(x == nullptr) return y;}

#define CreateTextRender()\
{\
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);\
	Text->SetRelativeLocation(FVector(0, 0, 100));\
	Text->SetRelativeRotation(FRotator(0, 100, 0));\
	Text->SetRelativeScale3D(FVector(2));\
	Text->TextRenderColor = FColor::Red;\
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;\
	Text->Text = FText::FromString(GetName().Replace(TEXT("Default__"), TEXT("")));\
}


class MYUNREALCPP_01_API CHelpers
{
public:
	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*OutComponent)->SetupAttachment(InParent);

			return;
		}

		InActor->SetRootComponent(*OutComponent);
	}

	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		*OutObject = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		*OutClass = asset.Class;
	}

	template<typename T>
	static T* FindActor(UWorld* InWorld)
	{
		for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
		{
			if (!!actor && actor->IsA<T>())
				return Cast<T>(actor);
		}

		return nullptr;
	}

	template<typename T>
	static void FindActors(UWorld* InWorld, TArray<T*>& OutActors)
	{
		for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
		{
			if (!!actor && actor->IsA<T>())
				OutActors.Add(Cast<T>(actor));
		}
	}

};