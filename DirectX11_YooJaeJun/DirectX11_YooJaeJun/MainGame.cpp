#include "framework.h"

MainGame::~MainGame()
{
    KillTimer(g_hwnd, NULL);
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

    /*
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
    */

    cc.position.x = 400.0f;
    cc.position.y = 300.0f;
    cc.scale.x = 500.0f;
    cc.scale.y = 500.0f;
    cc.rotation = 0.0f;

    lnHour.position.x = 400.0f;
    lnHour.position.y = 300.0f;
    lnHour.scale.x = 180.0f;
    lnHour.scale.y = 180.0f;
    lnHour.rotation = 0.0f;

    lnMinute.position.x = 400.0f;
    lnMinute.position.y = 300.0f;
    lnMinute.scale.x = 300.0f;
    lnMinute.scale.y = 300.0f;
    lnMinute.rotation = 0.0f;

    lnSecond.position.x = 400.0f;
    lnSecond.position.y = 300.0f;
    lnSecond.scale.x = 400.0f;
    lnSecond.scale.y = 400.0f;
    lnSecond.rotation = 0.0f;

	// WM_TIMER 메시지를 일정주기마다 발생
	//					n 밀리초마다 발생
	// SetTimer(g_hwnd, 1, 10, NULL);		// 17 밀리초 == 60 fps
}

void MainGame::Update()
{
    GetLocalTime(&localTime);


	// GetAsyncKeyState 메시지큐를 거치지 않고 키입력을 받아오는 함수
    //가상키코드

    // 이전호출  호출상태  비트상태  
    // X         X        0000
    // O         X        0001  // 키 뗌 UP
    // X         O        1000  // 키 누름 DOWN
    // O         O        1001  // 키 누르고 있음 PRESS
    /*
    if (INPUT->KeyPress(VK_UP))
    {
        rc.position += Vector2(cosf(DIV2PI * 3.0f), sinf(DIV2PI * 3.0f)) 
            * 100.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        rc.position += Vector2(cosf(DIV2PI), sinf(DIV2PI))
            * 100.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        rc.position += Vector2(cosf(PI), sinf(PI))
            * 100.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        rc.position += Vector2(cosf(0), sinf(0))
            * 100.0f * DELTA;
    }
    if (INPUT->KeyPress('1'))
    {
        rc.scale.x += DELTA * 100.0f;
    }
    if (INPUT->KeyPress('2'))
    {
        rc.scale.x -= DELTA * 100.0f;
    }
    if (INPUT->KeyPress('3'))
    {
        rc.scale.y += DELTA * 100.0f;
    }
    if (INPUT->KeyPress('4'))
    {
        rc.scale.y -= DELTA * 100.0f;
    }
    if (INPUT->KeyPress('5'))
    {
        rc.rotation += DELTA * 10.0f;
    }
    if (INPUT->KeyPress('6'))
    {
        rc.rotation -= DELTA * 10.0f;
    }

    rc.Update();
    st.Update();
    */

    cc.Update();
    lnHour.Update();
    lnMinute.Update();
    lnSecond.Update();

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

    /*
    rc.Render();
    st.Render();
    */
    cc.Render();
    lnHour.RenderClock(localTime.wHour * 60 / 24);
    lnMinute.RenderClock(localTime.wMinute);
    lnSecond.RenderClock(localTime.wSecond);


    //고속 복사 g_MemDC에서 g_hdc로
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
