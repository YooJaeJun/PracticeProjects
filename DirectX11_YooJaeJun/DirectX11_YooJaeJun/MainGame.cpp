#include "framework.h"
// #define mode_basicShape
// #define mode_clock
#define mode_axis

MainGame::~MainGame()
{
    // KillTimer(g_hwnd, NULL);
}

void MainGame::Init()
{
    //MemDc 메모리상의 dc를 하나 더 추가
    HBITMAP	 m_hOldBitmap, m_hBitmap;
    HDC	hdc = GetDC(g_hwnd); //기존 핸들
    g_MemDC = CreateCompatibleDC(hdc);
    m_hBitmap = CreateCompatibleBitmap(hdc, 800, 600);//만들 크기 -> 처음 해상도 값
    m_hOldBitmap = (HBITMAP)SelectObject(g_MemDC, m_hBitmap);
    ReleaseDC(g_hwnd, hdc);


    // 사각형
#ifdef mode_basicShape
    rc.position.x = 400.0f;
    rc.position.y = 200.0f;
    rc.scale.x = 100.0f;
    rc.scale.y = 100.0f;
    rc.rotation = 0.0f;

    st.position.x = 100.0f;
    st.position.y = 200.0f;
    st.scale.x = 100.0f;
    st.scale.y = 100.0f;
    st.rotation = 0.0f;
#endif
    // 시계
#ifdef mode_clock
    lnHour.position.x = 400.0f;
    lnHour.position.y = 300.0f;
    lnHour.scale.x = 100.0f;
    lnHour.scale.y = 100.0f;
    lnHour.rotation = 0.0f;

    lnMinute.position.x = 400.0f;
    lnMinute.position.y = 300.0f;
    lnMinute.scale.x = 150.0f;
    lnMinute.scale.y = 150.0f;
    lnMinute.rotation = 0.0f;

    lnSecond.position.x = 400.0f;
    lnSecond.position.y = 300.0f;
    lnSecond.scale.x = 200.0f;
    lnSecond.scale.y = 200.0f;
    lnSecond.rotation = 0.0f;

    cc.position.x = 400.0f;
    cc.position.y = 300.0f;
    cc.scale.x = 500.0f;
    cc.scale.y = 500.0f;
    cc.rotation = 0.0f;
#endif
    // 축
#ifdef mode_axis
    // 태양
    planet[0].SetWorldPos(Vector2(400.0f, 300.0f));
    planet[0].scale.x = 100.0f;
    planet[0].scale.y = 100.0f;
    planet[0].rotation = 0.0f;
    planet[0].isAxis = true;

    for (int i = 0; i < planetNum; i++)
    {
        planet[i].SetLocalPos(Vector2(50.0f + i * 10.0f, 50.0f + i * 10.0f));
        planet[i].scale.x = 12.0f + i * 3;
        planet[i].scale.y = 12.0f + i * 3;
        planet[i].rotation = 0.0f;
        planet[i].isAxis = true;
        planet[i].SetParentRT(planet[0]);
    }
#endif

    // WM_TIMER 메시지를 일정주기마다 발생
    //					n 밀리초마다 발생
    // SetTimer(g_hwnd, 1, 10, NULL);		// 17 밀리초 == 60 fps
}

void MainGame::Update()
{
    GetLocalTime(&localTime);

    // 사각형
    // GetAsyncKeyState 메시지큐를 거치지 않고 키입력을 받아오는 함수
    //가상키코드
    // 이전호출  호출상태  비트상태  
    // X         X        0000
    // O         X        0001  // 키 뗌 UP
    // X         O        1000  // 키 누름 DOWN
    // O         O        1001  // 키 누르고 있음 PRESS

    // 사각형
#ifdef mode_basicShape
    rc.Update();
    st.Update();
#endif
    // 시계
#ifdef mode_clock
    // 스무스
    lnHour.rotation = -DIV2PI + (float)localTime.wHour * 30.0f * ToRadian
        + (float)localTime.wMinute * 0.5f * ToRadian;   // 1칸(30도)를 60분간 가야되서 0.5도씩

    lnMinute.rotation = -DIV2PI + (float)localTime.wMinute * 6.0f * ToRadian
        + (float)localTime.wSecond * 0.1f * ToRadian;   // 6도를 60초간

    lnSecond.rotation = -DIV2PI + (float)localTime.wSecond * 6.0f * ToRadian
        + (float)localTime.wMilliseconds * 0.006f * ToRadian;   //  (1000밀리세컨드 == 1초). 0.006

    // 똑딱
    /*
    lnHour.rotation = -DIV2PI + (float)localTime.wHour * 30.0f * ToRadian;
    lnMinute.rotation = -DIV2PI + (float)localTime.wMinute * 6.0f * ToRadian;
    lnSecond.rotation = -DIV2PI + (float)localTime.wSecond * 6.0f * ToRadian;
    */

    lnHour.Update();
    lnMinute.Update();
    lnSecond.Update();
    cc.Update();
#endif
    // 축
#ifdef mode_axis
    /*
    if (INPUT->KeyPress(VK_UP))
    {
        planet[1].MoveLocalPos(UP * 200.0f * DELTA);
        // cc1.position += UP * 200.0f * DELTA;
        // radian에 특정 float을 더한 것
        // cc.position += -Vector2(cosf(cc.rotation + DIV2PI), sinf(cc.rotation + DIV2PI)) * 150.0f * DELTA;
        // cc1.position += -cc1.GetDown() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        planet[1].MoveLocalPos(DOWN * 200.0f * DELTA);
        // cc1.position += DOWN * 200.0f * DELTA;
        // cc.position += Vector2(cosf(cc.rotation + DIV2PI), sinf(cc.rotation + DIV2PI)) * 150.0f * DELTA;
        // cc1.position += cc1.GetDown() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        planet[1].MoveLocalPos(LEFT * 200.0f * DELTA);
        // cc1.position += LEFT * 200.0f * DELTA;
        // cc.position += Vector2(cosf(cc.rotation + PI), sinf(cc.rotation + PI)) * 150.0f * DELTA;
        // cc1.position += -cc1.GetRight() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        planet[1].MoveLocalPos(RIGHT * 200.0f * DELTA);
        // cc1.position += RIGHT * 200.0f * DELTA;
        // cc.position += -Vector2(cosf(cc.rotation + PI), sinf(cc.rotation + PI)) * 150.0f * DELTA;
        // cc1.position += cc1.GetRight() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress('1'))
    {
        cc1.scale.x += DELTA * 150.0f;
    }
    if (INPUT->KeyPress('2'))
    {
        cc1.scale.x -= DELTA * 150.0f;
    }
    if (INPUT->KeyPress('3'))
    {
        cc1.scale.y += DELTA * 150.0f;
    }
    if (INPUT->KeyPress('4'))
    {
        cc1.scale.y -= DELTA * 150.0f;
    }
    if (INPUT->KeyPress('5'))
    {
        cc1.rotation += DELTA * 5.0f;
    }
    if (INPUT->KeyPress('6'))
    {
        cc1.rotation -= DELTA * 5.0f;
    }
    */
    if (INPUT->KeyPress('Q'))
    {
        planet[0].rotation -= DELTA * 360.0f * ToRadian;
    }
    if (INPUT->KeyPress('E'))
    {
        planet[0].rotation += DELTA * 360.0f * ToRadian;
    }

    for (int i = 1; i < planetNum; i++)
    {
        planet[i].rotation += 30.0f * i * ToRadian * DELTA;
        planet[i].rotation2 += 30.0f * i * ToRadian * DELTA;
    }

    for (int i = 0; i < planetNum; i++)
    {
        planet[i].Update();
    }

#endif

    //키가 눌렸을 때 wm_paint 를 발생 시켜라
    InvalidateRect(g_hwnd, NULL, false);
}

void MainGame::Render()
{
    PAINTSTRUCT ps;
    //hdc-> 도화지
    g_hdc = BeginPaint(g_hwnd, &ps);

    //바탕색 깔기
    PatBlt(g_MemDC, 0, 0, 800, 600, WHITENESS);


    // 사각형
#ifdef mode_basicShape
    rc.Render();
    st.Render();
#endif
    // 시계
#ifdef mode_clock 
    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), FPS.size());

    string time = "시간 : " + to_string(localTime.wHour) + "시 " +
        to_string(localTime.wMinute) + "분 " +
        to_string(localTime.wSecond) + "초 " +
        to_string(localTime.wMilliseconds) + "밀리초 ";
    TextOutA(g_MemDC, 0, 20, time.c_str(), time.size());

    string timeNum;
    for (int i = 1; i <= 12; i++)
    {
        timeNum = to_string(i);
        TextOutA(g_MemDC, 400 + 220 * cosf((i * 30 - 90) * ToRadian),
            300 + 220 * sinf((i * 30 - 90) * ToRadian),
            timeNum.c_str(), timeNum.size());
    }

    lnHour.Render();
    lnMinute.Render();
    lnSecond.Render();
    // lnHour.RenderClock(localTime.wHour * 60 / 24);
    // lnMinute.RenderClock(localTime.wMinute);
    // lnSecond.RenderClock(localTime.wSecond);
    cc.Render();
#endif
    // 축
#ifdef mode_axis
    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), FPS.size());
    string keyDesc = "회전 가속: Q, E";
    TextOutA(g_MemDC, 0, 20, keyDesc.c_str(), keyDesc.size());

    for (int i = 0; i < planetNum; i++)
    {
        planet[i].Render();
    }
#endif


    //고속 복사 g_MemDC에서 g_hdc로
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}