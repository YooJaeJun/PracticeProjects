#include "framework.h"

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

    // WM_TIMER �޽����� �����ֱ⸶�� �߻�
    //					n �и��ʸ��� �߻�
    // SetTimer(g_hwnd, 1, 10, NULL);		// 17 �и��� == 60 fps
#endif
    // ���� �׸�
#ifdef mode_shapeDrawing

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
    // ��(�¾��)
#ifdef mode_axis
    // �¾�
    planet[0].SetWorldPos(Vector2(400.0f, 300.0f));
    planet[0].SetScale(Vector2(100.0f, 100.0f));
    planet[0].rotation = 0.0f;
    planet[0].isAxis = true;

    for (int i = 1; i < planetNum - 5; i++)
    {
        planet[0].SetScale(Vector2(12.0f + i * 3, 12.0f + i * 3));
        planet[i].rotation = 0.0f;
        planet[i].isAxis = true;
        planet[i].SetParentRT(planet[0]);
    }
    planet[1].SetLocalPos(Vector2(50.0f, -50.0f));
    planet[2].SetLocalPos(Vector2(-100.0f, 100.0f));
    planet[3].SetLocalPos(Vector2(80.0f, 80.0f));
    planet[4].SetLocalPos(Vector2(120.0f, -120.0f));
    planet[5].SetLocalPos(Vector2(160.0f, 160.0f));


    for (int i = planetNum - 5; i < planetNum; i++)
    {
        planet[i].SetLocalPos(Vector2(2.0f + i * 2, 2.0f + i * 2));
        planet[0].SetScale(Vector2(8.0f, 8.0f));
        planet[i].rotation = 0.0f;
        planet[i].isAxis = true;
        planet[i].SetParentRT(planet[i - 5]);
    }


#endif
    // �Ѿ���ǳ
#ifdef mode_bulletStorm
    enemy = make_shared<Enemy>();
    enemy->SetLocalPos(Vector2(400, 300));
    enemy->SetScale(Vector2(100.0f, 100.0f));
    enemy->isAxis = true;

    bullet.resize(bulletNum);
    for (int i = 0; i < bulletNum; i++)
    {
        bullet[i] = make_shared<Bullet>
            (80.0f + i * 2.0f, 80.0f + i * 2.0f,
            50.0f, 50.0f,
            i * 2.0f, i * 3.0f, 10.0f);
        bullet[i]->SetParentRT(enemy);
    }
#endif
    //
#ifdef mode_pet
    player.SetWorldPos(Vector2(400.0f, 300.0f));
    player.SetScale(Vector2(100.0f, 100.0f));
    player.rotation = 0.0f;
    player.isAxis = true;

    pet.SetWorldPos(Vector2(100.0f, 100.0f));
    pet.SetScale(Vector2(30.0f, 30.0f));
    pet.rotation = 0.0f;
    pet.isAxis = true;
    pet.SetParentRT(player);

    arrow.SetWorldPos(Vector2(2000.0f, 2000.0f));
    arrow.SetScale(Vector2(30.0f, 0.0f));
    arrow.rotation = 0.0f;
    arrow.isAxis = true;

    isFired = false;
#endif
}

void MainGame::Update()
{
    // �簢��
#ifdef mode_basicShape
    // GetAsyncKeyState �޽���ť�� ��ġ�� �ʰ� Ű�Է��� �޾ƿ��� �Լ�
    //����Ű�ڵ�
    // ����ȣ��  ȣ�����  ��Ʈ����  
    // X         X        0000
    // O         X        0001  // Ű �� UP
    // X         O        1000  // Ű ���� DOWN
    // O         O        1001  // Ű ������ ���� PRESS
    rc.Update();
    st.Update();
#endif
    // �����׸�
#ifdef mode_shapeDrawing
    if (INPUT->KeyPress(VK_LEFT)) { posX -= 3; posHumanX -= 3; }
    if (INPUT->KeyPress(VK_RIGHT)){ posX += 3; posHumanX += 3; }
    if (INPUT->KeyPress(VK_UP))   { posY -= 3; posHumanY -= 3; }
    if (INPUT->KeyPress(VK_DOWN)) { posY += 3; posHumanY += 3; }
    if (INPUT->KeyPress('1')) { scaleX += 0.1f; }
    if (INPUT->KeyPress('2')) { scaleX -= 0.1f; }
    if (INPUT->KeyPress('3')) { scaleY += 0.1f; }
    if (INPUT->KeyPress('4')) { scaleY -= 0.1f; }
    if (INPUT->KeyPress('5')) { seta += 0.1f; }
    if (INPUT->KeyPress('6')) { seta -= 0.1f; }
#endif
    // �ð�
#ifdef mode_clock
    GetLocalTime(&localTime);

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
    // ��(�¾��)
#ifdef mode_axis
    /*
    if (INPUT->KeyPress(VK_UP))
    {
        planet[1].MoveLocalPos(UP * 200.0f * DELTA);
        // cc1.position += UP * 200.0f * DELTA;
        // radian�� Ư�� float�� ���� ��
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
    */
    /*
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

    for (int i = 1; i < planetNum - 5; i++)
    {
        planet[i].rotation += 15.0f * i * ToRadian * DELTA;
        planet[i].rotation2 += 15.0f * i * ToRadian * DELTA;
    }
    for (int i = planetNum - 5; i < planetNum; i++)
    {
        planet[i].rotation += 5.0f * i * ToRadian * DELTA;
        planet[i].rotation2 -= 8.0f * i * ToRadian * DELTA;
    }

    for (int i = 0; i < planetNum; i++)
    {
        planet[i].Update();
    }
#endif
    // �Ѿ���ǳ
#ifdef mode_bulletStorm
    enemy->Update();

    if (INPUT->KeyPress('Q'))
    {
        enemy->rotation -= DELTA * 360.0f * ToRadian;
        qState = true;
    }
    else qState = false;

    if (INPUT->KeyPress('E'))
    {
        enemy->rotation += DELTA * 360.0f * ToRadian;
        eState = true;
    }
    else eState = false;

    for (int i = 0; i < bulletNum; i++)
    {
        bullet[i]->rotation += 3.0f * i * ToRadian * DELTA;
        bullet[i]->rotation2 += 3.0f * i * ToRadian * DELTA;
        bullet[i]->Update();
    }
#endif
    // 
#ifdef mode_pet
    if (INPUT->KeyPress(VK_UP))
    {
        player.MoveWorldPos(-player.GetDown() * 200.0f * DELTA);
    }
    else if (INPUT->KeyPress(VK_DOWN))
    {
        player.MoveWorldPos(player.GetDown() * 200.0f * DELTA);
    }
    if (INPUT->KeyPress(VK_LEFT))
    {
        player.rotation -= 120.0f * ToRadian * DELTA;
    }
    else if (INPUT->KeyPress(VK_RIGHT))
    {
        player.rotation += 120.0f * ToRadian * DELTA;
    }
    
    if (INPUT->KeyPress(VK_SPACE))
    {
        isFired = true;
        arrow.SetWorldPos(player.GetWorldPos());
        arrow.rotation = DirToRadian(player.GetRight());
        // arrow.SetWorldPos(pet.GetWorldPos());
        // arrow.rotation = DirToRadian(pet.GetRight());
    }

    if (isFired) arrow.MoveWorldPos(arrow.GetRight() * 200.0f * DELTA);

    if (INPUT->KeyDown('R'))    // ������
    {
        isFired = false;
        arrow.SetWorldPos(player.GetWorldPos());
    }

    if (INPUT->KeyPress(VK_SPACE)) arrow.SetWorldPos(player.GetWorldPos());
    pet.rotation2 += 50.0f * ToRadian * DELTA;

    player.Update();
    pet.Update();
    arrow.Update();

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
    // �����׸�
#ifdef mode_shapeDrawing
    // �޴�
    MoveToEx(g_MemDC, posX, posY, NULL);
    for (int i = 0; i <= 720; i += 10)
    {
        LineTo(g_MemDC, posX + i / 5 * cosf(i * R + seta) * scaleX,
            posY + i / 5 * sinf(i * R + seta) * scaleY);
    }
    MoveToEx(g_MemDC, posX, posY, NULL);
    for (int i = 0; i <= 720; i += 10)
    {
        LineTo(g_MemDC, posX - i / 5 * cosf(i * R + seta) * scaleX,
            posY - i / 5 * sinf(i * R + seta) * scaleY);
    }

    // ��������
    for (int i = 30; i <= 360; i += 30)
    {
        MoveToEx(g_MemDC, posX + 170 * cosf(i * R + seta) * scaleX,
            posY + 170 * sinf(i * R + seta) * scaleY, NULL);
        LineTo(g_MemDC, posX + 250 * cosf(i * R + seta) * scaleX,
            posY + 250 * sinf(i * R + seta) * scaleY);
    }

    // ��
    MoveToEx(g_MemDC, posHumanX + 120 * cosf(0 * R + seta) * scaleX,
        posHumanY + 120 * sinf(0 * R + seta) * scaleY, NULL);
    for (int i = 40; i <= 360; i += 40)
    {
        LineTo(g_MemDC, posHumanX + 120 * cosf(i * R + seta) * scaleX,
            posHumanY + 120 * sinf(i * R + seta) * scaleY);
    }

    // ��
    // ����
    MoveToEx(g_MemDC, posHumanX + 50 * cosf(200 * R + seta) * scaleX,
        posHumanY + 50 * sinf(200 * R + seta) * scaleY, NULL);
    LineTo(g_MemDC, posHumanX + 50 * cosf(140 * R + seta) * scaleX,
        posHumanY + 50 * sinf(140 * R + seta) * scaleY);

    MoveToEx(g_MemDC, posHumanX + 70 * cosf(170 * R + seta) * scaleX,
        posHumanY + 70 * sinf(170 * R + seta) * scaleY, NULL);
    LineTo(g_MemDC, posHumanX + 10 * cosf(170 * R + seta) * scaleX,
        posHumanY + 10 * sinf(170 * R + seta) * scaleY);
    // ������
    MoveToEx(g_MemDC, posHumanX + 50 * cosf(310 * R + seta) * scaleX,
        posHumanY + 50 * sinf(310 * R + seta) * scaleY, NULL);
    LineTo(g_MemDC, posHumanX + 50 * cosf(250 * R + seta) * scaleX,
        posHumanY + 50 * sinf(250 * R + seta) * scaleY);

    MoveToEx(g_MemDC, posHumanX + 70 * cosf(280 * R + seta) * scaleX,
        posHumanY + 70 * sinf(280 * R + seta) * scaleY, NULL);
    LineTo(g_MemDC, posHumanX + 20 * cosf(280 * R + seta) * scaleX,
        posHumanY + 20 * sinf(280 * R + seta) * scaleY);

    // ��
    MoveToEx(g_MemDC, posHumanX + 70 * cosf(10 * R + seta) * scaleX,
        posHumanY + 70 * sinf(10 * R + seta) * scaleY, NULL);
    LineTo(g_MemDC, posHumanX + 30 * cosf(25 * R + seta) * scaleX,
        posHumanY + 30 * sinf(25 * R + seta) * scaleY);
    LineTo(g_MemDC, posHumanX + 60 * cosf(70 * R + seta) * scaleX,
        posHumanY + 60 * sinf(70 * R + seta) * scaleY);
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
    // ��(�¾��)
#ifdef mode_axis
    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), FPS.size());
    string keyDesc = "ȸ�� ����: Q, E";
    TextOutA(g_MemDC, 0, 20, keyDesc.c_str(), keyDesc.size());

    for (int i = 0; i < planetNum; i++)
    {
        if (i == 6 || i == 8 || i == 9) continue;
        planet[i].Render();
    }
#endif
    // �Ѿ���ǳ
#ifdef mode_bulletStorm
    string FPS = "FPS : " + to_string(TIMER->GetFPS());
    TextOutA(g_MemDC, 0, 0, FPS.c_str(), (int)FPS.size());
    string keyDesc = "ȸ�� ����: Q, E";
    TextOutA(g_MemDC, 0, 20, keyDesc.c_str(), (int)keyDesc.size());
    string keyHoldDesc = "������";
    if (qState || eState) TextOutA(g_MemDC, 375, 295, keyHoldDesc.c_str(), (int)keyHoldDesc.size());

    enemy->Render();

    for (int i = 0; i < bulletNum; i++)
    {
        bullet[i]->Render();
    }
    
#endif
    //
#ifdef mode_pet
    player.Render();
    pet.Render();
    arrow.Render();
#endif

    //��� ���� g_MemDC���� g_hdc��
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}