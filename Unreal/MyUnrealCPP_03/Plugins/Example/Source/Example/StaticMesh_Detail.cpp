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
    actor.SetCategoryVisibility(false);

    IDetailCategoryBuilder& mesh = DetailBuilder.EditCategory("Mesh");

    IDetailCategoryBuilder& lighting = DetailBuilder.EditCategory("Lighting");
    // lighting.Get CastShadow


    // 검색어명
    mesh.AddCustomRow(FText::FromString("Mesh"))
    .NameContent()
    [
        SNew(STextBlock)
        .Text(FText::FromString("Color"))
    ];
}
