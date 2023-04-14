#pragma once
#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FStaticMesh_DetailData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> Uvs;
	TArray<int32> Indices;

	FVector Extent;
	float Radius;

	friend FArchive& operator<<(FArchive& InArchive, FStaticMesh_DetailData& InValue)
	{
		return InArchive
			<< InValue.Positions
			<< InValue.Normals
			<< InValue.Uvs
			<< InValue.Colors
			<< InValue.Indices
			<< InValue.Extent
			<< InValue.Radius;
	}
};

class EXAMPLE_API FStaticMesh_Detail
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_Paint();
	FReply OnClicked_SaveMesh();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
	//TWeakObjectPtr 지역변수 약참조
	//TWeakFieldPtr  멤버변수 약참조
};
