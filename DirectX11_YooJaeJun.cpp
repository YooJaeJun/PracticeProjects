#include "framework.h"

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
Scene*              mg;         // 추상화
HDC                 g_hdc;
HDC                 g_MemDC;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//**윈도우 프로시저** (프로시저) -> 호출 당하는 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//창사이즈 재조정   바탕화면 좌표
void SetWindowSize(int x, int y, int width, int height);

// ATOM                MyRegisterClass(HINSTANCE hInstance);
// BOOL                InitInstance(HINSTANCE, int);
// LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


/*
    WCHAR
    wchar_t 형식을 TYPEDEF 으로 별칭을 사용한 구문입니다.
    wide character 형식이라 불립니다.
    넓은 형태 (아스키코드로 표현하지 못하는 문자)를 표현할 수 있습니다.
    char(8bit) 와 다르게 16bit(2Byte) 형식을 저장하므로 보다 넓은 문자를 사용할 수 있습니다.
    L"" : wide char 형식의 문자열 상수 표기법입니다.
*/
WCHAR     szTitle[100] = L"😊😁👍🤣🎁🐱‍🚀🎉😁😘👍🙌🤦‍♀️🎶😎😉🤞✌🤷‍♂️🤷‍♀️🤦‍♂️🌹🎂🤳😃👀";       // 창의 제목을 저장하는 전역변수입니다.
WCHAR     szWindowClass[100] = L"Window";     // 윈도우 클래스 이름을 저장하는 전역변수입니다.


// wWinMain : 창 프로그램의 시작 위치를 결정합니다.
// main     : 콘솔 프로그램의 시작 위치를 결정합니다.
// APIENTRY : __stdcall 의 심볼입니다.
// __stdcall : 프로그래머가 직접 호출해주는 것이 아닌 컴퓨터가 자동으로 호출해준 함수 호출 규정 방식
int APIENTRY wWinMain(_In_    HINSTANCE hInstance,      // 우리가 실행하고 있는 프로그램의 시작 위치를 저장합니다.
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow)
{
    // 윈도우 클래스
    WNDCLASS wc;

    // NULL값으로 시작주소부터 크기까지 초기화
    ZeroMemory(&wc, sizeof(WNDCLASS));

    // 참조하지 않은 인자에 대해 경고를 표시하지 않는다.
    UNREFERENCED_PARAMETER(lpCmdLine);
    // 비트연산자
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    // 프로시져 넘기기 L(함수 포이넡 변수) = R(함수 포인터)
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.hInstance = hInstance;
    // 아이콘(프로그램 왼쪽 위)
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // ShowCursor(false);

    // 윈도우창 바탕색
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
    wc.lpszClassName = L"DX11";
    wc.lpszMenuName = nullptr;

    // 운영체제의 레지스터에 이 프로그램을 등록한다.
    if (!RegisterClass(&wc))
        return FALSE;   // 등록이 안됐다면 프로그램 종료

    g_hInst = hInstance;

    mg = new MainGame();

    // 메인 윈도우 생성
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

    // 핸들이 제대로 값을 가지지 못했다면 프로그램 종료
    if (!g_hwnd)
        return FALSE;

    // 화면 작업 사이즈 영역 계산
    SetWindowSize(0, 0, 800, 600);

    // 생성한 프로그램을 디스플레이의 최상위로 올린다
    // 화면에 표시
    ShowWindow(g_hwnd, nCmdShow);

    // 메인 윈도우 갱신
    UpdateWindow(g_hwnd);

    mg->Init();

    // **메시지 루프**
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    // 기본 메시지 루프: 런타임동안 반복시킬 구문

#ifndef PEEK
    // 프로그램에 들어오는 메세지를 저장할 수 있는 구조체
    // GetMessage : 대기하고 있는 메세지를 가져와 MSG 형태에 저장합니다.
    //              만약 메세지가 없다면 while 문을 잠재웁니다.
    //              WM_QUIT 메시지가 돌아온다면 false 를 반환합니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        DispatchMessage(&msg);
    }
#endif  // !PEEK

#ifdef PEEK
    while (true)
    {
        // PeekMessage : 대기하고 있는 메시지가 있는지 없는지 검사합니다.
        //               만약 메시지가 없다면 false,
        //               있다면 true 를 반환하고 MSG 형태에 저장합니다.
        // GetMessage 발생한 메시지를 줄 때까지 계속 기다려서 받는 애
        // Peek 발생할 때만 집어서 가져오는 애
        if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;

            // 처리
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 메시지를 집어오지 않을 때   // 1 프레임
            TIMER->Chronometry();
            INPUT->Update();
            mg->Update();
            mg->Render();
        }
    }
    // 프로그램 종료 준비

    // 생성된 윈도우 삭제
    DestroyWindow(g_hwnd);
    // 등록된 프로그램 해제
    UnregisterClass(L"DX11", hInstance);

    return (int)msg.wParam;
    
#endif
    // PeekMessage 사용 이유
    // GetMessage 같은 경우 주기적으로 호출될 코드를 WM_TIMER 를 통하여 호출해야 합니다.
    // 이렇게 WM_TIMER 를 통하여 호출해야 합니다.
    // 해당과 같이 코드를 호출하게 되면 CPU 연산이 아닌 메시지를 통해 연산량을 결정하기 때문에 호출속도가 느립니다.
    // PeekMessage 같은 경우 while 과 같은 cpu 연산을 통하여 메시지가 없다면 주기적으로 호출할 코드를 실행시키기
    // 때문에 호출량 차이로 인하여 PeekMessage 를 사용합니다.
}

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

    case WM_CLOSE:
    case WM_DESTROY:    // 창이 파괴되었을 때의 메세지입니다.
        PostQuitMessage(0); // WM_QUIT 메세지를 보냅니다.
        break;

    // DefWindowProc : 우리가 케이스로 지정하지 않은 메세지를 자동으로 처리해주는 역할입니다.
    return DefWindowProc(hWnd, message, wParam, lParam);
    }
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