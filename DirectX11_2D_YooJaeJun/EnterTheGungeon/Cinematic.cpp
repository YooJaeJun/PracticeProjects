#include "stdafx.h"

namespace Gungeon
{
    Cinematic::Cinematic()
    {
        Init();
    }

    void Cinematic::Init()
    {
        for (auto& elem : cinematicBox)
        {
            elem = new UI;
            elem->img = new ObImage(L"EnterTheGungeon/Level/Cinematic_Box.png");
            elem->img->scale = Vector2(app.GetWidth(), 150.0f);
            elem->img->isFilled = true;
            elem->img->color = Color(0.0f, 0.0f, 0.0f);
            elem->img->space = Space::screen;
            elem->img->pivot = OFFSET_LT;
        }
        cinematicBox[0]->anchor = DirState::dirLT;
        cinematicBox[0]->Spawn(0.0f, 150.0f);
        cinematicBox[1]->anchor = DirState::dirLB;
        cinematicBox[1]->Spawn(0.0f, 0.0f);

        cinematicState = CinematicState::none;

        for (auto& elem : timeCinematic)
        {
            elem = 0.0f;
        }

        intervalCinematic[(int)CinematicState::cinematicBox1] = 1.0f;
        intervalCinematic[(int)CinematicState::cinematicBox2] = 1.0f;
        intervalCinematic[(int)CinematicState::cutScene] = 3.0f;
        intervalCinematic[(int)CinematicState::cinematicBox3] = 1.0f;
        intervalCinematic[(int)CinematicState::cinematicBox4] = 1.0f;
    }

    void Cinematic::Release()
    {
        for (auto& elem : cinematicBox) elem->Release();
    }

    void Cinematic::Update()
    {
        switch (cinematicState)
        {
            // 등장연출
        case Gungeon::CinematicState::none:
            break;
        case Gungeon::CinematicState::cinematicBox1:
            cinematicBox[0]->img->MoveWorldPos(Vector2(0.0f, -75.0f * DELTA));
            cinematicBox[1]->img->MoveWorldPos(Vector2(0.0f, 75.0f * DELTA));

            if (TIMER->GetTick(timeCinematic[(int)CinematicState::cinematicBox1],
                intervalCinematic[(int)CinematicState::cinematicBox1]))
            {
                cinematicState = CinematicState::cameraTargeting1;
            }
            break;
        case Gungeon::CinematicState::cameraTargeting1:
            break;
        case Gungeon::CinematicState::bossSpawnAnim:
            break;
        case Gungeon::CinematicState::cutScene:
            if (TIMER->GetTick(timeCinematic[(int)CinematicState::cutScene],
                intervalCinematic[(int)CinematicState::cutScene]))
            {
                cinematicState = CinematicState::cameraTargeting2;
            }
            break;
        case Gungeon::CinematicState::cameraTargeting2:
            break;
        case Gungeon::CinematicState::cinematicBox2:
            cinematicBox[0]->img->MoveWorldPos(Vector2(0.0f, 75.0f * DELTA));
            cinematicBox[1]->img->MoveWorldPos(Vector2(0.0f, -75.0f * DELTA));

            if (TIMER->GetTick(timeCinematic[(int)CinematicState::cinematicBox2],
                intervalCinematic[(int)CinematicState::cinematicBox2]))
            {
                cinematicState = CinematicState::finish;
            }
            break;
        case Gungeon::CinematicState::finish:
            break;

            // 사망연출
        case Gungeon::CinematicState::cinematicBox3:
            cinematicBox[0]->img->MoveWorldPos(Vector2(0.0f, -75.0f * DELTA));
            cinematicBox[1]->img->MoveWorldPos(Vector2(0.0f, 75.0f * DELTA));

            if (TIMER->GetTick(timeCinematic[(int)CinematicState::cinematicBox3],
                intervalCinematic[(int)CinematicState::cinematicBox3]))
            {
                cinematicState = CinematicState::cameraTargeting3;
            }
            break;
        case Gungeon::CinematicState::cameraTargeting3:
            break;
        case Gungeon::CinematicState::bossDieAnim:
            break;
        case Gungeon::CinematicState::cameraTargeting4:
        case Gungeon::CinematicState::cinematicBox4:
            cinematicBox[0]->img->MoveWorldPos(Vector2(0.0f, 75.0f * DELTA));
            cinematicBox[1]->img->MoveWorldPos(Vector2(0.0f, -75.0f * DELTA));

            if (TIMER->GetTick(timeCinematic[(int)CinematicState::cinematicBox4],
                intervalCinematic[(int)CinematicState::cinematicBox4]))
            {
                cinematicState = CinematicState::finish2;
            }
        case Gungeon::CinematicState::finish2:
            break;
        case Gungeon::CinematicState::clear:
            break;
        }

        for (auto& elem : cinematicBox) elem->Update();
    }

    void Cinematic::Render()
    {
        for (auto& elem : cinematicBox) elem->Render();
    }
}