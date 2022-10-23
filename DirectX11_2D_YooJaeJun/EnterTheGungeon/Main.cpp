#include "stdafx.h"
#include "Main.h"
using namespace Gungeon;

void Main::Init()
{
    LIGHT->light.radius = 2000.0f;
    LIGHT->light.select = 0.0f;

    InitSound();

    mapGen = new ProcedureMapGeneration;
    player = new Player;

    {
        Scene01* tempScene = new Scene01();
        tempScene->mapGen = mapGen;
        tempScene->player = player;
        SCENE->AddScene("Scene01", tempScene);
    }

    SCENE->ChangeScene("Scene01");
}

void Gungeon::Main::InitSound()
{
    SOUND->AddSound("EnterTheGungeon/MapGenBGM.ogg", "MapGenBGM", true);
    SOUND->AddSound("EnterTheGungeon/GameBGM.ogg", "GameBGM", true);
    SOUND->AddSound("EnterTheGungeon/BossBGM.ogg", "BossBGM", true);
    SOUND->AddSound("EnterTheGungeon/Roll.ogg", "Roll", false);
    SOUND->AddSound("EnterTheGungeon/Fall.ogg", "Fall", false);
    SOUND->AddSound("EnterTheGungeon/Respawn.ogg", "Respawn", false);
    SOUND->AddSound("EnterTheGungeon/Death.ogg", "Death", false);
    SOUND->AddSound("EnterTheGungeon/Pistol.ogg", "Pistol", false);
    SOUND->AddSound("EnterTheGungeon/Shotgun.ogg", "Shotgun", false);
    SOUND->AddSound("EnterTheGungeon/MachineGun.ogg", "MachineGun", false);
    SOUND->AddSound("EnterTheGungeon/Reload.ogg", "Reload", false);
    SOUND->AddSound("EnterTheGungeon/EmptyBullet.ogg", "EmptyBullet", false);
    SOUND->AddSound("EnterTheGungeon/Bomb.ogg", "Bomb", false);
    SOUND->AddSound("EnterTheGungeon/Dust.ogg", "Dust", false);
    SOUND->AddSound("EnterTheGungeon/Coin.ogg", "Coin", false);
    SOUND->AddSound("EnterTheGungeon/FootstepStone.ogg", "FootstepStone", false);
    SOUND->AddSound("EnterTheGungeon/BookCharge.ogg", "BookCharge", false);
    SOUND->AddSound("EnterTheGungeon/BookAttack.ogg", "BookAttack", false);
    SOUND->AddSound("EnterTheGungeon/BookDrop.ogg", "BookDrop", false);
    SOUND->AddSound("EnterTheGungeon/BulletManDeath.ogg", "BulletManDeath", false);
    SOUND->AddSound("EnterTheGungeon/BulletManHurt.ogg", "BulletManHurt", false);
    SOUND->AddSound("EnterTheGungeon/BossIntro.ogg", "BossIntro", false);
    SOUND->AddSound("EnterTheGungeon/BulletKingChairDown.ogg", "BulletKingChairDown", false);
    SOUND->AddSound("EnterTheGungeon/BulletKingShot.ogg", "BulletKingShot", false);
    SOUND->AddSound("EnterTheGungeon/BulletKingThrow.ogg", "BulletKingThrow", false);
    SOUND->AddSound("EnterTheGungeon/BulletKingSpin.ogg", "BulletKingSpin", false);
    SOUND->AddSound("EnterTheGungeon/SpawnByForce.ogg", "SpawnByForce", false);
    SOUND->AddSound("EnterTheGungeon/FinalShot.ogg", "FinalShot", false);
    SOUND->AddSound("EnterTheGungeon/Win.ogg", "Win", false);
    SOUND->AddSound("EnterTheGungeon/ChestUnlock.ogg", "ChestUnlock", false);
    SOUND->AddSound("EnterTheGungeon/ChestOpen.ogg", "ChestOpen", false);
    SOUND->AddSound("EnterTheGungeon/WeaponPickup.ogg", "WeaponPickup", false);
    SOUND->AddSound("EnterTheGungeon/GateSlam.ogg", "GateSlam", false);
    SOUND->AddSound("EnterTheGungeon/GateOpen.ogg", "GateOpen", false);
    SOUND->AddSound("EnterTheGungeon/DoorClosed.ogg", "DoorClosed", false);
}

void Main::Release()
{
    SafeRelease(mapGen);
    SafeRelease(player);
    SCENE->Release();
}

void Main::Update()
{
    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Enter the Gungeon by 유재준");
    app.SetInstance(instance);
    app.InitWidthHeight(1400.0f, 740.0f);
    app.background = Color(0.0f, 0.0f, 0.0f, 1.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}
