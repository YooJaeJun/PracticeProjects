#include "framework.h"

MainGame::~MainGame()
{
    KillTimer(g_hwnd, NULL);
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


    cc.position.x = 400.0f;
    cc.position.y = 300.0f;
    cc.scale.x = 100.0f;
    cc.scale.y = 100.0f;
    cc.rotation = 0.0f;

    cc.isAxis = true;

    // �簢��
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

    // �ð�
    /*
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
    */
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
    
    if (INPUT->KeyPress(VK_UP))
    {
        cc.position += Vector2(cosf(cc.rotation + PI + DIV2PI), sinf(cc.rotation + PI + DIV2PI)) * 150.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        cc.position += Vector2(cosf(cc.rotation + DIV2PI), sinf(cc.rotation + DIV2PI)) * 150.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        cc.position += Vector2(cosf(cc.rotation + PI), sinf(cc.rotation + PI)) * 150.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        cc.position += Vector2(cosf(cc.rotation), sinf(cc.rotation)) * 150.0f * DELTA;
    }
    if (INPUT->KeyPress('1'))
    {
        cc.scale.x += DELTA * 150.0f;
    }
    if (INPUT->KeyPress('2'))
    {
        cc.scale.x -= DELTA * 150.0f;
    }
    if (INPUT->KeyPress('3'))
    {
        cc.scale.y += DELTA * 150.0f;
    }
    if (INPUT->KeyPress('4'))
    {
        cc.scale.y -= DELTA * 150.0f;
    }
    if (INPUT->KeyPress('5'))
    {
        cc.rotation += DELTA * 10.0f;
    }
    if (INPUT->KeyPress('6'))
    {
        cc.rotation -= DELTA * 10.0f;
    }


    // rc.Update();
    // st.Update();
    

    // �ð�
    /*
    lnHour.rotation = -DIV2PI + (float)localTime.wHour * 30.0f * ToRadian
        + (float)localTime.wMinute * 0.5f * ToRadian;   // 1ĭ(30��)�� 60�а� ���ߵǼ� 0.5����

    lnMinute.rotation = -DIV2PI + (float)localTime.wMinute * 6.0f * ToRadian
        + (float)localTime.wSecond * 0.1f * ToRadian;   // 6���� 60�ʰ�

    lnSecond.rotation = -DIV2PI + (float)localTime.wSecond * 6.0f * ToRadian
        + (float)localTime.wMilliseconds * 0.006f * ToRadian;   //  (1000�и������� == 1��). 0.006
    */

    cc.Update();
    // lnHour.Update();
    // lnMinute.Update();
    // lnSecond.Update();

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


    cc.Render();

    // �簢��
    /*
    rc.Render();
    st.Render();
    */
    // �ð�
    /*
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
    */
    // lnHour.Render();
    // lnMinute.Render();
    // lnSecond.Render();
    // lnHour.RenderClock(localTime.wHour * 60 / 24);
    // lnMinute.RenderClock(localTime.wMinute);
    // lnSecond.RenderClock(localTime.wSecond);


    //��� ���� g_MemDC���� g_hdc��
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
