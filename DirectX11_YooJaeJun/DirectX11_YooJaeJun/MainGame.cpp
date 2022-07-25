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
    //MemDc �޸𸮻��� dc�� �ϳ� �� �߰�
    HBITMAP	 m_hOldBitmap, m_hBitmap;
    HDC	hdc = GetDC(g_hwnd); //���� �ڵ�
    g_MemDC = CreateCompatibleDC(hdc);
    m_hBitmap = CreateCompatibleBitmap(hdc, 800, 600);//���� ũ�� -> ó�� �ػ� ��
    m_hOldBitmap = (HBITMAP)SelectObject(g_MemDC, m_hBitmap);
    ReleaseDC(g_hwnd, hdc);


    // �簢��
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
    // �ð�
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
    // ��
#ifdef mode_axis

    for (int i = 0; i < planetNum; i++)
    {
        planetParent[i].position.x = 400.0f;
        planetParent[i].position.y = 300.0f;
        planetParent[i].scale.x = 100.0f;
        planetParent[i].scale.y = 100.0f;
        planetParent[i].rotation = 0.0f;
        planetParent[i].isAxis = true;
    }

    planet[0].position.x = 400.0f;
    planet[0].position.y = 300.0f;
    planet[0].scale.x = 100.0f;
    planet[0].scale.y = 100.0f;
    planet[0].rotation = 0.0f;
    planet[0].isAxis = true;

    planet[1].position.x = 50.0f;
    planet[1].position.y = 50.0f;
    planet[1].scale.x = 12.0f;
    planet[1].scale.y = 12.0f;
    planet[1].rotation = 0.0f;
    planet[1].isAxis = true;
    planet[1].p = &planetParent[1].RT;

    planet[2].position.x = 80.0f;
    planet[2].position.y = -80.0f;
    planet[2].scale.x = 17.0f;
    planet[2].scale.y = 17.0f;
    planet[2].rotation = 0.0f;
    planet[2].isAxis = true;
    planet[2].p = &planetParent[2].RT;

    planet[3].position.x = -150.0f;
    planet[3].position.y = -50.0f;
    planet[3].scale.x = 20.0f;
    planet[3].scale.y = 20.0f;
    planet[3].rotation = 0.0f;
    planet[3].isAxis = true;
    planet[3].p = &planetParent[3].RT;

    planet[4].position.x = 200.0f;
    planet[4].position.y = 30.0f;
    planet[4].scale.x = 25.0f;
    planet[4].scale.y = 25.0f;
    planet[4].rotation = 0.0f;
    planet[4].isAxis = true;
    planet[4].p = &planetParent[4].RT;

    planet[5].position.x = 120.0f;
    planet[5].position.y = 280.0f;
    planet[5].scale.x = 30.0f;
    planet[5].scale.y = 30.0f;
    planet[5].rotation = 0.0f;
    planet[5].isAxis = true;
    planet[5].p = &planetParent[5].RT;
#endif

    // WM_TIMER �޽����� �����ֱ⸶�� �߻�
    //					n �и��ʸ��� �߻�
    // SetTimer(g_hwnd, 1, 10, NULL);		// 17 �и��� == 60 fps
}

void MainGame::Update()
{
    GetLocalTime(&localTime);

    // �簢��
    // GetAsyncKeyState �޽���ť�� ��ġ�� �ʰ� Ű�Է��� �޾ƿ��� �Լ�
    //����Ű�ڵ�
    // ����ȣ��  ȣ�����  ��Ʈ����  
    // X         X        0000
    // O         X        0001  // Ű �� UP
    // X         O        1000  // Ű ���� DOWN
    // O         O        1001  // Ű ������ ���� PRESS

    // �簢��
#ifdef mode_basicShape
    rc.Update();
    st.Update();
#endif
    // �ð�
#ifdef mode_clock
    // ������
    lnHour.rotation = -DIV2PI + (float)localTime.wHour * 30.0f * ToRadian
        + (float)localTime.wMinute * 0.5f * ToRadian;   // 1ĭ(30��)�� 60�а� ���ߵǼ� 0.5����

    lnMinute.rotation = -DIV2PI + (float)localTime.wMinute * 6.0f * ToRadian
        + (float)localTime.wSecond * 0.1f * ToRadian;   // 6���� 60�ʰ�

    lnSecond.rotation = -DIV2PI + (float)localTime.wSecond * 6.0f * ToRadian
        + (float)localTime.wMilliseconds * 0.006f * ToRadian;   //  (1000�и������� == 1��). 0.006

    // �ȵ�
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
    // ��
#ifdef mode_axis
    /*
    if (INPUT->KeyPress(VK_UP))
    {
        cc1.position += UP * 200.0f * DELTA;
        // radian�� Ư�� float�� ���� ��
        // cc.position += -Vector2(cosf(cc.rotation + DIV2PI), sinf(cc.rotation + DIV2PI)) * 150.0f * DELTA;
        // cc1.position += -cc1.GetDown() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        cc1.position += DOWN * 200.0f * DELTA;
        // cc.position += Vector2(cosf(cc.rotation + DIV2PI), sinf(cc.rotation + DIV2PI)) * 150.0f * DELTA;
        // cc1.position += cc1.GetDown() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        cc1.position += LEFT * 200.0f * DELTA;
        // cc.position += Vector2(cosf(cc.rotation + PI), sinf(cc.rotation + PI)) * 150.0f * DELTA;
        // cc1.position += -cc1.GetRight() * 200.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        cc1.position += RIGHT * 200.0f * DELTA;
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
        for (int i = 0; i < planetNum; i++)
        {
            planetParent[i].rotation -= DELTA * 7.0f;
        }
        planet[0].rotation -= DELTA * 7.0f;
    }
    if (INPUT->KeyPress('E'))
    {
        for (int i = 0; i < planetNum; i++)
        {
            planetParent[i].rotation += DELTA * 7.0f;
        }
        planet[0].rotation += DELTA * 7.0f;
    }

    planetParent[1].rotation += DELTA * 0.2f;
    planet[1].rotation += DELTA * 0.3f;

    planetParent[2].rotation += DELTA * 1.4f;
    planet[2].rotation += DELTA * 1.0f;

    planetParent[3].rotation += DELTA * 0.7f;
    planet[3].rotation += DELTA * 0.6f;

    planetParent[4].rotation += DELTA * 1.5f;
    planet[4].rotation += DELTA * 1.2f;

    planetParent[5].rotation += DELTA * 0.5f;
    planet[5].rotation += DELTA * 0.5f;


    for (int i = 0; i < planetNum; i++)
    {
        planetParent[i].Update();
        planet[i].Update();
    }

#endif

    //Ű�� ������ �� wm_paint �� �߻� ���Ѷ�
    InvalidateRect(g_hwnd, NULL, false);
}

void MainGame::Render()
{
    PAINTSTRUCT ps;
    //hdc-> ��ȭ��
    g_hdc = BeginPaint(g_hwnd, &ps);

    //������ ���
    PatBlt(g_MemDC, 0, 0, 800, 600, WHITENESS);


    // �簢��
#ifdef mode_basicShape
    rc.Render();
    st.Render();
#endif
    // �ð�
#ifdef mode_clock 
    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), FPS.size());

    string time = "�ð� : " + to_string(localTime.wHour) + "�� " +
        to_string(localTime.wMinute) + "�� " +
        to_string(localTime.wSecond) + "�� " +
        to_string(localTime.wMilliseconds) + "�и��� ";
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
    // ��
#ifdef mode_axis
    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), FPS.size());
    string keyDesc = "ȸ�� ����: Q, E";
    TextOutA(g_MemDC, 0, 20, keyDesc.c_str(), keyDesc.size());

    for (int i = 0; i < planetNum; i++)
    {
        planet[i].Render();
    }
#endif


    //��� ���� g_MemDC���� g_hdc��
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}