#include "ButtonCommand.h"
#include "Misc/MessageDialog.h"
#include "Misc/FileHelper.h"
#include "Serialization/BufferArchive.h"
#include "DesktopPlatformModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "StaticMesh_Detail.h"
#include "Editor.h"
#include "LevelEditorViewport.h"
#include "CStaticMesh_Copied.h"

FButtonCommand::FButtonCommand()
    : TCommands("ToolBar_Buttons", FText(), NAME_None, FEditorStyle::GetStyleSetName())
{
    Command = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
    if (Command.IsValid())
        Command.Reset();
}

void FButtonCommand::RegisterCommands()
{
    // LOCTEXT_DEFINE_REGION 디파인 되어있을 경우
#define LOCTEXT_NAMESPACE ""
    UI_COMMAND(LoadMesh, "LoadMesh", "", EUserInterfaceActionType::Button, FInputChord()/*단축키*/);
#undef LOCTEXT_NAMESPACE 

    Command->MapAction(LoadMesh, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked_LoadMesh));
}

void FButtonCommand::OnClicked_LoadMesh()
{
    GLog->Log("OnClick");

    IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
    void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();    // 핸들 가변. 4 or 8바이트

    FString path;
    FPaths::GetPath(path);  // 이전에 열었던 패스 리턴

    TArray<FString> fileNames;

    IDesktopPlatform* platform = FDesktopPlatformModule::Get();
    platform->SaveFileDialog(handle, "Open Mesh File", path, "", "mesh Binary File(*.bin)|*.bin",
        EFileDialogFlags::None, fileNames);     // */ wide character

    if (fileNames.Num() < 1)
        return;

    FBufferArchive buffer;
    FFileHelper::LoadFileToArray(buffer, *fileNames[0]);

    FMemoryReader reader = FMemoryReader(buffer, true);
    reader.Seek(0);

    FStaticMesh_DetailData data;
    reader << data;
    reader.FlushCache();
    reader.Close();

    GLog->Logf(L"Vertex Count : %d", data.Positions.Num());
    GLog->Logf(L"Triangle Count : %d", data.Indices.Num() / 3);
    GLog->Logf(L"Extent : %s", *data.Extent.ToString());
    GLog->Logf(L"Radius : %f", data.Radius);

    FString text;
    for (int32 i = 0; i < data.Positions.Num(); i++)
    {
        text.Append(data.Positions[i].ToString() + ", ");
        text.Append(data.Normals[i].ToString() + ", ");
        text.Append(data.Uvs[i].ToString() + ", ");
        text.Append(data.Colors[i].ToString() + "\r\n");
    }

    FString textFileName = FPaths::GetBaseFilename(fileNames[0], false);
    FString textSaveName = textFileName + "_Copied.csv";

    FFileHelper::SaveStringToFile(text, *textSaveName);

    FLevelEditorViewportClient* client = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
    if (client == nullptr)
    {
        // GLog->Log("Client");
        return;
    }
    // GLog->Log("Viewport Client");

    FVector start = client->GetViewLocation();
    FVector end = start + client->GetViewRotation().RotateVector(FVector(10000, 0, 0));

    FHitResult hitResult;
    UWorld* world = GEditor->GetEditorWorldContext().World();

    world->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility);

    if (hitResult.bBlockingHit == false)
    {
        FMessageDialog dialog;
        dialog.Debugf(FText::FromString("Can't be placed in this location."));

        return;
    }

    FTransform transform;
    FVector direction = (hitResult.TraceEnd - hitResult.TraceStart);
    direction.Normalize();

    FVector location = hitResult.TraceStart + direction * (hitResult.Distance - data.Radius);
    transform.SetLocation(location);

    FRotator rotator = FRotator(0, direction.Rotation().Yaw, 0);
    transform.SetRotation(FQuat(rotator));

    ACStaticMesh_Copied* actor = world->SpawnActorDeferred<ACStaticMesh_Copied>
        (
            ACStaticMesh_Copied::StaticClass(),
            transform,
            nullptr,
            nullptr,
            ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
        );

    actor->SetPositions(data.Positions);
    actor->SetIndices(data.Indices);
    actor->SetNormals(data.Normals);
    actor->SetUvs(data.Uvs);
    actor->SetColors(data.Colors);

    actor->FinishSpawning(transform);
}