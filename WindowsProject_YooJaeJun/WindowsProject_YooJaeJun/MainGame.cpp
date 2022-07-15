#include "framework.h"

void MainGame::Init()
{
	// MemDC �޸𸮻��� dc�� �ϳ� �� �߰�
	HBITMAP m_hOldBitmap, m_hBitmap;
	HDC hdc = GetDC(g_hwnd);
	g_MemDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(g_MemDC, 800, 600);
	// m_hOldBitmap = CreateCompatibleBitmap(g_MemDC, g_MemDC, m_hBitmap);
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
	
}

void MainGame::Render()
{

	rc.Render();
	st.Render();
	cc.Render();

	// ������ ���
	PatBlt(g_MemDC, 0, 0, 800, 600, WHITENESS);


	// ��� ���� g_MemDC���� g_hdc��
	BitBlt(g_MemDC, 0, 0, 800, 600, 
		g_hdc, 0, 0, WHITENESS);


	// ����Ű�ڵ�
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		rc.position.y -= 3.0f;
	}
}
