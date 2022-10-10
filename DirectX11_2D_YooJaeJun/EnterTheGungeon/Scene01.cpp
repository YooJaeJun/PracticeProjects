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
        if (mapGen) mapGen->useGui = true;

        CAM->position = Vector2(0.0f, 0.0f);
        CAM->zoomFactor = Vector3(0.08f, 0.08f, 0.08f);

        fadeOut = false;
        timeFade = 0.0f;

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
        if (INPUT->KeyDown('R') || INPUT->KeyDown('1'))
        {
            mapGen->Release();
            mapGen->Init();
        }
        if (mapGen) mapGen->Update();

        if (INPUT->KeyDown('2'))
        {
            fadeOut = true;
            SCENE->ChangeScene("Scene02", 2.0f);
        }

        ChangeUpdateScene();
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

    void Scene01::ChangeUpdateScene()
    {
        if (fadeOut)
        {
            LIGHT->light.radius -= 1000.0f * DELTA;

            if (TIMER->GetTick(timeFade, 2.0f))
            {
                fadeOut = false;
            }
        }
        else
        {
            LIGHT->light.radius += 1000.0f * DELTA;
            LIGHT->light.radius = Utility::Saturate(LIGHT->light.radius, 0.0f, 2000.0f);
        }
    }
}