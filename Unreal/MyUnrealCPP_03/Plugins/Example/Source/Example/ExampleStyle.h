#pragma once

#include "CoreMinimal.h"
class EXAMPLE_API FExampleStyle
{
public:
	static TSharedPtr<FExampleStyle> Get();
	static void Shutdown();

public:
	static TSharedPtr<FExampleStyle> Instance;

public:
	FExampleStyle();
	~FExampleStyle();

private:
	void RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon);

private:
	static const FName StyleSetName;
	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	FSlateIcon ToolBar_LoadMesh_Icon;
};
