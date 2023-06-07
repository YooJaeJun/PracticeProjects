#include "SWeaponLeftArea.h"
#include "Weapons/CWeaponAsset.h"
#include "EngineUtils.h"
#include "Widgets/Input/SSearchBox.h"

void SWeaponTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)
{
	Data = InArgs._RowData;

	SMultiColumnTableRow<FWeaponRowDataPtr>::Construct
	(
		FSuperRowType::FArguments().Style(FEditorStyle::Get(), "TableView.DarkRow"), InOwnerTable
	);
}

TSharedRef<SWidget> SWeaponTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	FString str;
	if (InColumnName == "Number")
		str = FString::FromInt(Data->Number);
	else if (InColumnName == "Name")
		str = Data->Name;

	return SNew(STextBlock)
		.Text(FText::FromString(str));
}

///////////////////////////////////////////////////////////////////////////////

void SWeaponLeftArea::Construct(const FArguments& InArgs)
{
	OnListViewSelectedItem = InArgs._OnSelectedItem;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(2, 0)
		[
			SAssignNew(SearchBox, SSearchBox)
			.SelectAllTextWhenFocused(true)
			.OnTextChanged(this, &SWeaponLeftArea::OnTextChanged)
			.OnTextCommitted(this, &SWeaponLeftArea::OnTextCommitted)
		]
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(ListView, SListView<FWeaponRowDataPtr>)
			.HeaderRow
			(
				SNew(SHeaderRow)
				+ SHeaderRow::Column("Number")
				.DefaultLabel(FText::FromString(""))
				.ManualWidth(40)
				+ SHeaderRow::Column("Name")
				.DefaultLabel(FText::FromString("Name"))
			)
			.ListItemsSource(&RowDatas)
			.OnGenerateRow(this, &SWeaponLeftArea::OnGenerateRow)
			.OnSelectionChanged(this, &SWeaponLeftArea::OnSelectionChanged)
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(FMargin(8, 2))
		[
			SNew(STextBlock)
			.Text(this, &SWeaponLeftArea::OnGetAssetCount)
		]
	];

	ReadDataAssetList();
}

void SWeaponLeftArea::SelectDataPtr(UCWeaponAsset* InAsset)
{
	if (HasRowDataPtr() == false)
		return;

	for (FWeaponRowDataPtr ptr : RowDatas)
	{
		if (ptr->Asset == InAsset)
		{
			ListView->SetSelection(ptr);

			return;
		}
	}
}

TSharedRef<ITableRow> SWeaponLeftArea::OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable)
{
	return SNew(SWeaponTableRow, InTable)
		.RowData(InRow);
}

void SWeaponLeftArea::ReadDataAssetList()
{
	RowDatas.Empty();

	TArray<UObject*> objects;
	EngineUtils::FindOrLoadAssetsByPath("/Game/Weapons/", objects, EngineUtils::ATL_Regular);

	int32 index = 0;
	for (UObject* obj : objects)
	{
		UCWeaponAsset* asset = Cast<UCWeaponAsset>(obj);
		if (asset == nullptr)
			continue;

		FString name = asset->GetName();
		if (SearchText.IsEmpty() == false)
		{
			if (name.Contains(SearchText.ToString()) == false)
				continue;
		}

		RowDatas.Add(FWeaponRowData::Make(++index, name, asset));
	}

	RowDatas.Sort([](const FWeaponRowDataPtr& A, const FWeaponRowDataPtr& B)
	{
		return A->Number < B->Number;
	});

	ListView->RequestListRefresh();
}

FText SWeaponLeftArea::OnGetAssetCount() const
{
	FString str = FString::Printf(L"%d 에셋", RowDatas.Num());

	return FText::FromString(str);
}

void SWeaponLeftArea::OnTextChanged(const FText& InText)
{
	if (SearchText.CompareToCaseIgnored(InText) == 0)
		return;

	SearchText = InText;
	ReadDataAssetList();
}

void SWeaponLeftArea::OnTextCommitted(const FText& InText, ETextCommit::Type InType)
{
	OnTextChanged(InText);
}

void SWeaponLeftArea::OnSelectionChanged(FWeaponRowDataPtr InDataPtr, ESelectInfo::Type InType)
{
	if (InDataPtr.IsValid() == false)
		return;

	OnListViewSelectedItem.ExecuteIfBound(InDataPtr);
}