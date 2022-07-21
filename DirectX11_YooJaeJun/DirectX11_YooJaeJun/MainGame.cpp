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

    cc.position.x = 400.0f;
    cc.position.y = 300.0f;
    cc.scale.x = 500.0f;
    cc.scale.y = 500.0f;
    cc.rotation = 0.0f;

    ln.position.x = 400.0f;
    ln.position.y = 300.0f;
    ln.scale.x = 250.0f;
    ln.scale.y = 250.0f;
    ln.rotation = 0.0f;

	// WM_TIMER �޽����� �����ֱ⸶�� �߻�
	//					n �и��ʸ��� �߻�
	// SetTimer(g_hwnd, 1, 10, NULL);		// 17 �и��� == 60 fps
}

void MainGame::Update()
{
    GetLocalTime(&localTime);


	// GetAsyncKeyState �޽���ť�� ��ġ�� �ʰ� Ű�Է��� �޾ƿ��� �Լ�
    //����Ű�ڵ�

    // ����ȣ��  ȣ�����  ��Ʈ����  
    // X         X        0000
    // O         X        0001  // Ű �� UP
    // X         O        1000  // Ű ���� DOWN
    // O         O        1001  // Ű ������ ���� PRESS
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
    cc.Update();
    ln.Update();

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

    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), FPS.size());

    string time = "�ð� : " + to_string(localTime.wHour) + "�� " +
        to_string(localTime.wMinute) + "�� " +
        to_string(localTime.wSecond) + "�� " +
        to_string(localTime.wMilliseconds) + "�и��� ";
    TextOutA(g_MemDC, 0, 40, time.c_str(), time.size());

    rc.Render();
    st.Render();
    cc.Render();
    ln.Render();

    //��� ���� g_MemDC���� g_hdc��
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
