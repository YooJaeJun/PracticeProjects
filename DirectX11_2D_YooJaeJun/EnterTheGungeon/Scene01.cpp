#include "stdafx.h"

namespace Gungeon
{
    Scene01::Scene01()
    {
    }

    Scene01::~Scene01()
    {
    }

    void Scene01::Init()
    {
        CAM->position = Vector2(0.0f, 0.0f);
        CAM->coefScale = Vector3(0.08f, 0.08f, 0.08f);

        SOUND->Stop("SCENE02");
        //SOUND->AddSound("Vaquero Perdido - The Mini Vandals.mp3", "SCENE01", true);
        SOUND->Play("SCENE01");

        SOUND->AddSound("gun.wav", "GUN", false);
    }

    void Scene01::Release()
    {
    }

    void Scene01::Update()
    {
        if (INPUT->KeyDown('R'))
        {
            mapGen->Release();
            mapGen->Init();
        }
        if (mapGen) mapGen->Update();

        if (INPUT->KeyDown('2'))
        {
            SCENE->ChangeScene("Scene02");
        }
    }

    void Scene01::LateUpdate()
    {
        if (mapGen) mapGen->LateUpdate();
    }

    void Scene01::Render()
    {
        if (mapGen) mapGen->Render();
    }

    void Scene01::ResizeScreen()
    {
        if (mapGen) mapGen->ResizeScreen();
    }
}