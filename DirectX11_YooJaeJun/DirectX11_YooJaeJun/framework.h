#include <windows.h>
#include <iostream>
#include <math.h>

#include "SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

#define ToRadian  0.0174532

#include "GameObject.h"
#include "ObRect.h"
#include "ObStar.h"
#include "ObCircle.h"

#include "Types.h"
#include "Input.h"
#include "MainGame.h"

#define INPUT Input::GetInstance()

extern HINSTANCE	g_hInst;
extern HWND			g_hwnd;
extern Scene*		mg;
extern HDC			g_hdc;
extern HDC			g_MemDC;