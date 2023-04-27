#include "ExampleStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

const FName FExampleStyle::StyleSetName = "ExampleStyle";

TSharedPtr<FExampleStyle> FExampleStyle::Instance = nullptr;

TSharedPtr<FExampleStyle> FExampleStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FExampleStyle());

	return Instance;
}

void FExampleStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}

FExampleStyle::FExampleStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = FPaths::ProjectPluginsDir() / "Example" / "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("ToolBar_LoadMesh", path / "Icon128.png", FVector2D(52, 52), ToolBar_LoadMesh_Icon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

FExampleStyle::~FExampleStyle()
{
	if (StyleSet.IsValid() == false)
		return;

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	StyleSet.Reset();
}

void FExampleStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InIconSize);

	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);

	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(name));
}
