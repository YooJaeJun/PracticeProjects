#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FStaticMesh_Detail::MakeInstance()
{
	return MakeShareable(new FStaticMesh_Detail());
}

void FStaticMesh_Detail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& actor = DetailBuilder.EditCategory("Actor");
    // actor.SetCategoryVisibility(false);

    TArray<TSharedRef<IPropertyHandle>> handles;
    actor.GetDefaultProperties(handles);

    for (TSharedRef<IPropertyHandle> handle : handles)
    {
        //GLog->Log(handle->GetProperty()->GetName());
        //GLog->Log(handle->GetProperty()->GetPathName());
        //GLog->Log(handle->GetProperty()->GetFullName());

        if (handle->GetProperty()->GetName().Compare("bCanBeDamaged"))
            DetailBuilder.HideProperty(handle);
    }


    IDetailCategoryBuilder& mesh = DetailBuilder.EditCategory("Mesh");

    IDetailCategoryBuilder& lighting = DetailBuilder.EditCategory("Lighting");


    // 검색어명
    mesh.AddCustomRow(FText::FromString("Mesh"))
    .NameContent()
    [
        SNew(STextBlock)
        .Text(FText::FromString("Color"))
    ]
    .ValueContent()
        [
        SNew(SButton)
        .VAlign(VAlign_Center)
        .HAlign(HAlign_Fill)
        .OnClicked(this, &FStaticMesh_Detail::OnClicked_Paint)
        //.Content()
        [
            SNew(STextBlock)
            .Text(FText::FromString("Paint"))
        ]
    ];
}

FReply FStaticMesh_Detail::OnClicked_Paint()
{
    return FReply::Handled();
}
