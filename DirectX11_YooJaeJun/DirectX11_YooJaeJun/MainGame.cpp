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


	rc.position.x = 100.0f;
	rc.position.y = 200.0f;
	rc.scale.x = 1.0f;
	rc.scale.y = 1.0f;
	rc.rotation = 0.0f;

	st.position.x = 300.0f;
	st.position.y = 200.0f;
	st.scale.x = 1.0f;
	st.scale.y = 1.0f;
	st.rotation = 0.0f;

	cc.position.x = 500.0f;
	cc.position.y = 200.0f;
	cc.scale.x = 1.0f;
	cc.scale.y = 1.0f;
	cc.rotation = 0.0f;


	// WM_TIMER �޽����� �����ֱ⸶�� �߻�
	//					n �и��ʸ��� �߻�
	SetTimer(g_hwnd, 1, 17, NULL);		// 17 �и��� == 60 fps
}

void MainGame::Update()
{

	// GetAsyncKeyState �޽���ť�� ��ġ�� �ʰ� Ű�Է��� �޾ƿ��� �Լ�
    //����Ű�ڵ�

    // ����ȣ��  ȣ�����  ��Ʈ����  
    // X         X        0000
    // O         X        0001  // Ű �� UP
    // X         O        1000  // Ű ���� DOWN
    // O         O        1001  // Ű ������ ���� PRESS
    if (INPUT->KeyPress(VK_UP))
    {
        rc.position.y -= 3.0f;
        st.position.y -= 3.0f;
        cc.position.y -= 3.0f;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        rc.position.y += 3.0f;
        st.position.y += 3.0f;
        cc.position.y += 3.0f;
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        rc.position.x -= 3.0f;
        st.position.x -= 3.0f;
        cc.position.x -= 3.0f;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        rc.position.x += 3.0f;
        st.position.x += 3.0f;
        cc.position.x += 3.0f;
    }
    if (GetAsyncKeyState('1') & 0x8001)
    {
        rc.scale.x += 0.1f;
        st.scale.x += 0.1f;
        cc.scale.x += 0.1f;
    }
    if (GetAsyncKeyState('2') & 0x8001)
    {
        rc.scale.x -= 0.1f;
        st.scale.x -= 0.1f;
        cc.scale.x -= 0.1f;
    }
    if (GetAsyncKeyState('3') & 0x8001)
    {
        rc.scale.y += 0.1f;
        st.scale.y += 0.1f;
        cc.scale.y += 0.1f;
    }
    if (GetAsyncKeyState('4') & 0x8001)
    {
        rc.scale.y -= 0.1f;
        st.scale.y -= 0.1f;
        cc.scale.y -= 0.1f;
    }
    if (GetAsyncKeyState('5') & 0x8001)
    {
        rc.rotation += 0.1f;
        st.rotation += 0.1f;
        cc.rotation += 0.1f;
    }
    if (GetAsyncKeyState('6') & 0x8001)
    {
        rc.rotation -= 0.1f;
        st.rotation -= 0.1f;
        cc.rotation -= 0.1f;
    }


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

    rc.Render();
    st.Render();
    cc.Render();

    //��� ���� g_MemDC���� g_hdc��
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
