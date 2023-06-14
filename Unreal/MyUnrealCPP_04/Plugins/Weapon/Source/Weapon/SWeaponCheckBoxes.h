#pragma once

#include "CoreMinimal.h"

class WEAPON_API SWeaponCheckBoxes
	: public TSharedFromThis<SWeaponCheckBoxes>
{
public:
	void AddProperties(TSharedPtr<IPropertyHandle> InHandle);

	TSharedRef<SWidget> Draw(bool bBackground = false);
	void DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder* InChildrenBuilder);

	void SetUtilities(TSharedPtr<class IPropertyUtilities> InUtilities);

private:
	void OnCheckStateChanged(ECheckBoxState InState, int32 InIndex);

public:
	static bool CanDraw(TSharedPtr<IPropertyHandle> InHandle, int InCount);

public:
	void CheckDefaultObject(int32 InIndex, UObject* InValue);
	void CheckDefaultValue(int32 InIndex, float InValue);
	void CheckDefaultValue(int32 InIndex, bool InValue);
	void CheckDefaultValue(int32 InIndex, const FVector& InValue);

private:
	struct FInternalData
	{
		bool bChecked;
		FString Name;
		TSharedPtr<IPropertyHandle> Handle;

		FInternalData(TSharedPtr<IPropertyHandle> InHandle)
		{
			bChecked = false;
			Handle = InHandle;

			Name = Handle->GetPropertyDisplayName().ToString();
		}
	};
	TArray<FInternalData> InternalDatas;

	TSharedPtr<class IPropertyUtilities> Utilities;
};
