#include "framework.h"
// #include "화면 좌표계.txt"
#define R 0.01744444
#define MAX 20

//c++ - 칼질, 조리법

//WINAPI - 레토르트
//기본 템플릿

//핸들 -> 관리 감독
//H 접두어         리소스 핸들 (자원 관리자)
//HFONT,HBITMAP....
//HWND 접두어      Windows 핸들(창 관리자)
HINSTANCE           g_hInst;    //프로그램 자체의 관리자         // 기본 창 클래스 이름입니다.
HWND                g_hwnd;     //창 관리자                     // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//**윈도우 프로시저** (프로시저) -> 호출 당하는 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//창사이즈 재조정   바탕화면 좌표
void SetWindowSize(int x, int y, int width, int height);

//메인 진입 함수
//윈도우를 만들고 화면에 출력
int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    //윈도우 클래스
    WNDCLASS wc;

    //NULL값으로 시작주소부터 크기까지 초기화
    ZeroMemory(&wc, sizeof(WNDCLASS));

    //참조하지 않은 인자에 대해 경고를 표시하지 않는다
    UNREFERENCED_PARAMETER(lpCmdLine);
    //| & ^ 비트연산자
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    //프로시져 넘기기 L(함수 포인터 변수) = R(함수 포인터)
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.hInstance = hInstance;
    //아이콘(프로그램 왼쪽위)
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    //윈도우창 활성화시에 마우스커서 모양
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    //ShowCursor(false);

    //윈도우창 바탕색
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
    wc.lpszClassName = L"DX11";
    wc.lpszMenuName = nullptr;

    //	운영체제의 레지스터에 이 프로그램을 등록한다
    if (!RegisterClass(&wc))
        return FALSE; //등록이 안됬다면 프로그램 종료

     //생성된 인스턴스값 저장
    g_hInst = hInstance;

    //	메인 윈도우 생성
    g_hwnd = CreateWindow(
        L"DX11",
        L"DX11",
        WS_OVERLAPPEDWINDOW,
        0,			//창의 시작 x좌표
        0,			//창의 시작 y좌표
        800,		//창의 너비
        600,		//창의 높이
        nullptr,
        nullptr,
        hInstance,	//등록될 인스턴스
        nullptr
    );
    //핸들이 제대로 값을 가지지 못했다면 프로그램 종료
    if (!g_hwnd)
        return FALSE;

    //화면 작업 사이즈 영역 계산
    SetWindowSize(0, 0, 800, 600);

    //	생성한 프로그램을 디스플레이의 최상위로 올린다
    //화면에 표시
    ShowWindow(g_hwnd, nCmdShow);

    //	메인 윈도우 갱신
    UpdateWindow(g_hwnd);

    //**메시지 루프**
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    // 기본 메시지 루프입니다
    //런타임동안 반복시킬 반복문
    while (true)
    {
        //GetMessage 발생한 메세지를 줄 때까지 계속 기다려서 받는 애
        //Peek 발생할 때만 집어서 가져오는애
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            //처리
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //메세지를 집어오지 않을때
        }
    }
    //프로그램 종료 준비

     //생성된 윈도우 삭제
    DestroyWindow(g_hwnd);
    //등록된 프로그램 해제
    UnregisterClass(L"DX11", hInstance);

    return (int)msg.wParam;
}

float posX = 400.0f;
float posY = 300.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float seta = 1.0f;

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //어떤 메세지가 발생되었는가를 통해 처리할 조건문
    switch (message)
    {
        //그리라는 메세지가 들어온경우
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        //hdc-> 도화지
        HDC hdc = BeginPaint(hWnd, &ps);

        /*
        Ellipse(hdc, posX - 50 * scaleX, posY + 50 * scaleY,
            posX + 50 * scaleX, posY + 150 * scaleY);

        MoveToEx(hdc, posX - 50 * scaleX, posY, NULL);
        LineTo(hdc, posX + 50 * scaleX, posY); // ㅡ

        Ellipse(hdc, posX - 50 * scaleX, posY - 150 * scaleY,
            posX + 50 * scaleX, posY - 50 * scaleY);
        */

        /*
        //                   100 * cosf(0   * R + seta) == a             100 * sinf(0   * R + seta) == b
        MoveToEx(hdc, posX + 100 * cosf(0   * R + seta) * scaleX, posY + 100 * sinf(0   * R + seta) * scaleY, NULL);
        LineTo  (hdc, posX + 100 * cosf(120 * R + seta) * scaleX, posY + 100 * sinf(120 * R + seta) * scaleY);
        LineTo  (hdc, posX + 100 * cosf(240 * R + seta) * scaleX, posY + 100 * sinf(240 * R + seta) * scaleY);
        LineTo  (hdc, posX + 100 * cosf(0   * R + seta) * scaleX, posY + 100 * sinf(0   * R + seta) * scaleY);
        */

        //                   100 * cosf(0   * R + seta) == a             100 * sinf(0   * R + seta) == b
        MoveToEx(hdc, posX + 60 * cosf(0   * R + seta) * scaleX, posY + 60 * sinf(0   * R + seta) * scaleY, NULL);
        for (int i = 10; i <= 360; i += 5)
        {
            LineTo(hdc, posX + 60 * cosf(i * R + seta) * scaleX, posY + 60 * sinf(i * R + seta) * scaleY);
        }



        EndPaint(hWnd, &ps);
        break;
    }
    //파괴하거나 닫으라는 메세지가 들어온경우
    case WM_DESTROY: case WM_CLOSE:
    {
        //프로그램 종료 호출 함수
        PostQuitMessage(0);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        MessageBoxA(g_hwnd, "내용", "이름", MB_OK);
    }
    case WM_KEYDOWN:
    {
        InvalidateRect(hWnd, NULL, true);

        if (wParam == VK_LEFT)
        {
            posX -= 3;
        }
        if (wParam == VK_RIGHT)
        {
            posX += 3;
        }
        if (wParam == VK_UP)
        {
            posY -= 3;
        }
        if (wParam == VK_DOWN)
        {
            posY += 3;
        }

        if (wParam == '1')
        {
            scaleX += 0.1f;
        }
        if (wParam == '2')
        {
            scaleX -= 0.1f;
        }
        if (wParam == '3')
        {
            scaleY += 0.1f;
        }
        if (wParam == '4')
        {
            scaleY -= 0.1f;
        }

        if (wParam == '5')
        {
            seta += 0.1f;
        }
        if (wParam == '6')
        {
            seta -= 0.1f;
        }
    }
    }

    return (DefWindowProc(hWnd, message, wParam, lParam));
}

void SetWindowSize(int x, int y, int width, int height)
{
    //화면크기에 맞는 렉트
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = width;
    rc.bottom = height;

    //실제 윈도우 크기 조정
    AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU, false);
    //위 RECT 정보로 윈도우 사이즈 세팅
    SetWindowPos(g_hwnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}
