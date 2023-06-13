#include "SWeaponDoActionData.h"

#include "SWeaponCheckBoxes.h"

TArray<TSharedPtr<class SWeaponCheckBoxes>> SWeaponDoActionData::CheckBoxes;


TSharedRef<IPropertyTypeCustomization> SWeaponDoActionData::MakeInstance()
{
	return MakeShareable(new SWeaponDoActionData());
}

TSharedPtr<SWeaponCheckBoxes> SWeaponDoActionData::AddCheckBoxes()
{
	TSharedPtr<SWeaponCheckBoxes> checkBoxes = MakeShareable(new SWeaponCheckBoxes());
	int32 index = CheckBoxes.Add(checkBoxes);

	return CheckBoxes[index];
}

void SWeaponDoActionData::EmptyCheckBoxes()
{
	for (TSharedPtr<SWeaponCheckBoxes> ptr : CheckBoxes)
	{
		if (ptr.IsValid())
			ptr.Reset();
	}

	CheckBoxes.Empty();
}

void SWeaponDoActionData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow,
                                          IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	GLog->Log("CustomizeHeader");
}

void SWeaponDoActionData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
	IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	GLog->Log("CustomizeChildren");
}
