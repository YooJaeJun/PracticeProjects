#include <Windows.h>

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
WCHAR     szTitle[100]       = L"게임";       // 창의 제목을 저장하는 전역변수입니다.
WCHAR     szWindowClass[100] = L"Window";     // 윈도우 클래스 이름을 저장하는 전역변수입니다.

/*
    HINSTANCE (Instance Handle)
    프로세서의 실행 위치를 주소값을 반환한 형식입니다.
    프로세서란 현재 실행하고 있는 프로그램을 의미하며 프로그램은 컴퓨터 메모리에서
    특정 위치에서 실행합니다. 우리의 프로그램에 접근하기 위해서 어디에서 실행하고 있는지
    알고 있어야 하는데 그 위치를 저장할 수 있는 기법입니다.
*/
HINSTANCE hInst;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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

    while (GetMessage(&msg, nullptr, 0, 0))
    { DispatchMessage(&msg); }

    return (int) msg.wParam;
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
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);             // 화면 배경을 설정합니다.
    wcex.lpszClassName  = szWindowClass;                        // 클래스 이름을 설정합니다.

    return RegisterClassExW(&wcex);                             // 창 클래스를 등록합니다.
}

// 등록한 클래스로 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   // CreateWindow : 등록한 클래스로 창을 만들어주는 매크로 함수입니다.
   //               창을 제대로 만들지 못했다면 nullptr 를 반환하고
   //               창을 제대로 만들었다면 만든 창의 시작 위치를 반환합니다.

   // HWND : Window 의 시작 위치를 저장할 수 있는 Window Handle 입니다.
   HWND hWnd = CreateWindowW
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

   if (!hWnd) return FALSE;

   ShowWindow(hWnd, nCmdShow);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}