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
    }

    void Scene01::Release()
    {
    }

    void Scene01::Update()
    {
        if (INPUT->KeyDown('1'))
        {
            mapGen->Release();
            mapGen->Init();
        }
        else if (INPUT->KeyDown('2'))
        {
            fadeOut = true;
            SCENE->ChangeScene("Scene02", 1.0f);
        }
        else if (INPUT->KeyDown('3'))
        {
            fadeOut = true;
            SCENE->ChangeScene("Scene03", 1.0f);
        }

        if (mapGen) mapGen->Update();

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
            LIGHT->light.radius -= 2000.0f * DELTA;
            LIGHT->light.lightColor.x += 0.5f * DELTA;
            LIGHT->light.lightColor.y += 0.5f * DELTA;
            LIGHT->light.lightColor.z += 0.5f * DELTA;

            if (TIMER->GetTick(timeFade, 1.0f))
            {
                fadeOut = false;
            }
        }
        else
        {
            LIGHT->light.radius += 2000.0f * DELTA;
            LIGHT->light.radius = Utility::Saturate(LIGHT->light.radius, 0.0f, 2000.0f);
            LIGHT->light.lightColor.x = 0.5f;
            LIGHT->light.lightColor.y = 0.5f;
            LIGHT->light.lightColor.z = 0.5f;
        }
    }
}