#include <Windows.h>
#include <iostream>

// #pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#define PEEK

/*
    WinAPI(Windows Application Programming Interface)
    Window      : OS (Operating System)
    Application : 응용 프로그램
    Interface   : 함수의 집합체
    윈도우가 제공하는 응용프로그램을 개발하는 함수들의 집합체
*/

/*
    WCHAR
    wchar_t 형식을 TYPEDEF 으로 별칭을 사용한 구문입니다.
    wide character 형식이라 불립니다.
    넓은 형태 (아스키코드로 표현하지 못하는 문자)를 사표현할 수 있습니다.
    char(8bit) 와 다르게 16bit(2Byte) 형식을 저장하므로 보다 넓은 문자를 사용할 수 있습니다.
    L"" : wide char 형식의 문자열 상수 표기법입니다.
*/
WCHAR     szTitle[100]       = L"😊😁👍🤣✔(●'◡'●)(❁´◡`❁)(❁´◡`❁)☆*: ";       // 창의 제목을 저장하는 전역변수입니다.
WCHAR     szWindowClass[100] = L"Window";     // 윈도우 클래스 이름을 저장하는 전역변수입니다.

/*
    HINSTANCE (Instance Handle)
    프로세서의 실행 위치를 주소값을 반환한 형식입니다.
    프로세서란 현재 실행하고 있는 프로그램을 의미하며 프로그램은 컴퓨터 메모리에서
    특정 위치에서 실행합니다. 우리의 프로그램에 접근하기 위해서 어디에서 실행하고 있는지
    알고 있어야 하는데 그 위치를 저장할 수 있는 기법입니다.
*/
//핸들 -> 관리 감독
//H 접두어         리소스 핸들 (자원 관리자)
//HFONT,HBITMAP....
//HWND 접두어      Windows 핸들(창 관리자)
HINSTANCE           g_hInst;    //프로그램 자체의 관리자         // 기본 창 클래스 이름입니다.
HWND                g_hwnd;     //창 관리자                     // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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

// wWinMain : 창 프로그램의 시작 위치를 결정합니다.
// main     : 콘솔 프로그램의 시작 위치를 결정합니다.
// APIENTRY : __stdcall 의 심볼입니다.
// __stdcall : 프로그래머가 직접 호출해주는 것이 아닌 컴퓨터가 자동으로 호출해준 함수 호출 규정 방식
int APIENTRY wWinMain(_In_    HINSTANCE hInstance,      // 우리가 실행하고 있는 프로그램의 시작 위치를 저장합니다.
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_     LPWSTR    lpCmdLine,
                     _In_     int       nCmdShow)
{
    MyRegisterClass(hInstance);

    // 창이 제대로 만들어지지 않았다면 프로그램을 종료합니다.
    if (!InitInstance(hInstance, nCmdShow))
    { return FALSE; }

    MSG msg;

#ifndef PEEK
    // 프로그램에 들어오는 메세지를 저장할 수 있는 구조체
    // GetMessage : 대기하고 있는 메세지를 가져와 MSG 형태에 저장합니다.
    //              만약 메세지가 없다면 while 문을 잠재웁니다.
    //              WM_QUIT 메시지가 돌아온다면 false 를 반환합니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    { DispatchMessage(&msg); }
#endif  // !PEEK

#ifdef PEEK
    while (true)
    {
        // PeekMessage : 대기하고 있는 메시지가 있는지 없는지 검사합니다.
        //               만약 메시지가 없다면 false,
        //               있다면 true 를 반환하고 MSG 형태에 저장합니다.
        if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) return (int)msg.wParam;

            DispatchMessage(&msg);
        }
        else
        {
            // std::cout << "Update ";
        }
    }
#endif
    // PeekMessage 사용 이유
    // GetMessage 같은 경우 주기적으로 호출될 코드를 WM_TIMER 를 통하여 호출해야 합니다.
    // 이렇게 WM_TIMER 를 통하여 호출해야 합니다.
    // 해당과 같이 코드를 호출하게 되면 CPU 연산이 아닌 메시지를 통해 연산량을 결정하기 때문에 호출속도가 느립니다.
    // PeekMessage 같은 경우 while 과 같은 cpu 연산을 통하여 메시지가 없다면 주기적으로 호출할 코드를 실행시키기
    // 때문에 호출량 차이로 인하여 PeekMessage 를 사용합니다.
}

// Window 를 만들기 위해 Window 구조(class)를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);                   // class 의 Size 를 결정합니다.
    wcex.style          = CS_HREDRAW | CS_VREDRAW;              // window style 을 결정합니다.
    // CS_HREDRAW | CS_VREDRAW : 수평, 수직으로 창의 크기를 변경했을 때 전부 다시 그려주도록 하는 스타일입니다.
    wcex.lpfnWndProc    = WndProc;                              // 메시지 처리 함수를 등록합니다.
    wcex.cbClsExtra     = 0;                                    // 클래스 여분의 메모리입니다.
    wcex.cbWndExtra     = 0;                                    // 윈도우 여분의 메모리입니다.
    wcex.hInstance      = hInstance;                            // Instance Handle 을 설정합니다.
    wcex.hIcon          = LoadIcon(nullptr, IDI_APPLICATION);   // 큰 아이콘을 설정합니다.
    wcex.hIconSm        = LoadIcon(nullptr, IDI_APPLICATION);   // 작은 아이콘을 설정합니다.
    wcex.lpszMenuName   = nullptr;                              // 메뉴 사용 여부를 결정합니다.
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);       // 커서 아이콘을 설정합니다.
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);             // 화면 배경을 설정합니다.
    wcex.lpszClassName  = szWindowClass;                        // 클래스 이름을 설정합니다.

    return RegisterClassExW(&wcex);                             // 창 클래스를 등록합니다.
}

// 등록한 클래스로 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst = hInstance;

   // CreateWindow : 등록한 클래스로 창을 만들어주는 매크로 함수입니다.
   //               창을 제대로 만들지 못했다면 nullptr 를 반환하고
   //               창을 제대로 만들었다면 만든 창의 시작 위치를 반환합니다.

   // HWND : Window 의 시작 위치를 저장할 수 있는 Window Handle 입니다.
   g_hwnd = CreateWindowW
   (
       szWindowClass,           // 등록할 클래스 이름
       szTitle,                 // 창의 제목
       WS_OVERLAPPEDWINDOW,     // 윈도우 스타일
       // WS_OVERLAPPEDWINDOW : 겹칠 수 있는 창의 스타일입니다.
       CW_USEDEFAULT,           // 창의 시작 위치 x
       0,                       // 창의 시작 위치 y
       CW_USEDEFAULT,           // 창의 너비
       0,                       // 창의 높이
       nullptr,                 // 부모 윈도우 핸들
       nullptr,                 // 메뉴
       hInstance,               // 인스턴스 핸들
       nullptr                  // 
   );

   if (!g_hwnd) return FALSE;

   //화면 작업 사이즈 영역 계산
   SetWindowSize(0, 0, 800, 600);

   ShowWindow(g_hwnd, nCmdShow);

   //	메인 윈도우 갱신
   UpdateWindow(g_hwnd);

   return TRUE;
}


int x = 100, y = 100;
int x2 = 100, y2 = 100;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
#ifndef PEEK
    case WM_CREATE:
        SetTimer(hWnd, 1, 1, NULL);
        break;
    case WM_TIMER:
        std::cout << "Update ";
        break;
#endif
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        // hdc -> 도화지
        HDC hdc = BeginPaint(hWnd, &ps);

        // 유
        Ellipse(hdc, x, y, x2 + 100, y2 + 100);
        MoveToEx(hdc, x - 50, y2 + 150, NULL);  // ㅡ
        LineTo(hdc, x2 + 150, y2 + 150);
        MoveToEx(hdc, x + 20, y2 + 150, NULL); 
        LineTo(hdc, x + 20, y2 + 250);
        MoveToEx(hdc, x2 + 80, y2 + 150, NULL);
        LineTo(hdc, x2 + 80, y2 + 250);

        // 재
        MoveToEx(hdc, x + 200, y + 50, NULL);
        LineTo(hdc, x2 + 300, y + 50);
        MoveToEx(hdc, x2 + 300, y + 50, NULL);
        LineTo(hdc, x + 200, y2 + 180);
        MoveToEx(hdc, x + 250, y + 120, NULL);
        LineTo(hdc, x2 + 300, y2 + 180);

        MoveToEx(hdc, x + 340, y + 20, NULL);
        LineTo(hdc, x + 340, y2 + 230);
        MoveToEx(hdc, x2 + 400, y, NULL);
        LineTo(hdc, x2 + 400, y2 + 250);
        MoveToEx(hdc, x + 340, y + 120, NULL);  // ㅐ의 -
        LineTo(hdc, x2 + 400, y + 120);

        // 준
        MoveToEx(hdc, x + 500, y, NULL);
        LineTo(hdc, x2 + 600, y);
        MoveToEx(hdc, x2 + 600, y, NULL);
        LineTo(hdc, x + 500, y2 + 100);
        MoveToEx(hdc, x + 550, y + 50, NULL);
        LineTo(hdc, x2 + 600, y2 + 100);

        MoveToEx(hdc, x + 460, y2 + 130, NULL);
        LineTo(hdc, x2 + 660, y2 + 130);
        MoveToEx(hdc, x + 560, y2 + 130, NULL);
        LineTo(hdc, x + 560, y2 + 200);

        MoveToEx(hdc, x + 500, y + 180, NULL);
        LineTo(hdc, x + 500, y2 + 250);
        MoveToEx(hdc, x + 500, y2 + 250, NULL);
        LineTo(hdc, x2 + 640, y2 + 250);

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_LBUTTONDOWN:
        // std::cout << "😊😁👍🤣";
        // MessageBox(hWnd, L"😊😁👍🤣✔(●'◡'●)(❁´◡`❁)(❁´◡`❁)☆*: .｡. o(≧▽≦)o .｡.:*☆(❁´◡`❁)(❁´◡`❁)☆*: .｡. o(≧▽≦)o .｡.:*☆☆*: .｡. o(≧▽≦)o .｡.:*☆(*/ω＼*)(*/ω＼*):-)(❁´◡`❁)(❁´◡`❁)(❁´◡`❁)", L"z_z", MB_OK);

        break;
    case WM_KEYDOWN :
        {
        InvalidateRect(hWnd, NULL, true);

        if (wParam == VK_LEFT)
        {
            x -= 8;
            x2 -= 8;
        }
        if (wParam == VK_RIGHT)
        {
            x += 8;
            x2 += 8;
        }
        if (wParam == VK_UP)
        {
            y -= 8;
            y2 -= 8;
        }
        if (wParam == VK_DOWN)
        {
            y += 8;
            y2 += 8;
        }

        if (wParam == '1')
        {
            x -= 8;
            x2 += 8;
        }
        if (wParam == '2')
        {
            x += 8;
            x2 -= 8;
        }
        if (wParam == '3')
        {
            y -= 8;
            y2 += 8;
        }
        if (wParam == '4')
        {
            y += 8;
            y2 -= 8;
        }


        // if (wParam == VK_SPACE)
        // {
        //     MessageBox(hWnd, L"ㅎㅎㅎㅎㅎㅎㅎ", L"ㅎ_ㅎ", MB_RETRYCANCEL);
        // }
        // if (wParam == 'A')
        //     for (int i = 0; i < 10000; i++)
        //     {
        //         std::cout << "A Click ";
        //     }
        }
        break;

    case WM_DESTROY:    // 창이 파괴되었을 때의 메세지입니다.
        PostQuitMessage(0); // WM_QUIT 메세지를 보냅니다.
        break;

    default:
        // DefWindowProc : 우리가 케이스로 지정하지 않은 메세지를 자동으로 처리해주는 역할입니다.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 과제

// 윈도우 프로시저
// 메시지 루프
// 메시지 큐
// 윈도우 메시지

// 방향키: 화살표 이동
// 1, 2, 3, 4번: 축소 확대 x, y


