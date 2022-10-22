#include "stdafx.h"

namespace Gungeon
{
    Scene01::Scene01()
    {
        Init();
    }

    Scene01::~Scene01()
    {
    }

    void Scene01::Init()
    {
        MAP->useGui = true;

        CAM->position = Vector2(0.0f, 0.0f);
        CAM->zoomFactor = Vector3(0.08f, 0.08f, 0.08f);

        int idx = 0;
        if (mapGen && mapGen->selectedRooms.size() > 0)
        {
            for (auto& elem : mapGen->selectedRooms)
            {
                if (idx == 1)
                {
                    elem->treasureSpawner->isVisible = true;
                }
                for (auto& enemySpawerElem : elem->enemySpawner)
                {
                    enemySpawerElem->isVisible = true;
                }
                idx++;
            }
        }

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
            MAP->Init();
            mapGen->Release();
            mapGen->Init();
        }
        else if (INPUT->KeyDown('2'))
        {
            isChangingScene = true;
            SCENE->ChangeScene("Scene02", 1.0f);
        }
        else if (INPUT->KeyDown('3'))
        {
            isChangingScene = true;
            SCENE->ChangeScene("Scene03", 1.0f);
        }


        if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('A'))
        {
            CAM->position.x -= 1500.0f * DELTA;
        }
        if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
        {
            CAM->position.x += 1500.0f * DELTA;
        }
        if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
        {
            CAM->position.y += 1500.0f * DELTA;
        }
        if (INPUT->KeyPress(VK_DOWN) || INPUT->KeyPress('S'))
        {
            CAM->position.y -= 1500.0f * DELTA;
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
        if (isChangingScene)
        {
            LIGHT->light.radius -= 2000.0f * DELTA;
            LIGHT->light.lightColor.x += 0.5f * DELTA;
            LIGHT->light.lightColor.y += 0.5f * DELTA;
            LIGHT->light.lightColor.z += 0.5f * DELTA;

            if (TIMER->GetTick(timeFade, 1.0f))
            {
                isChangingScene = false;
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