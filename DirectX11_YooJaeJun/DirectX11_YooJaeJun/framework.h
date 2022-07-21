﻿#include <windows.h>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>

using namespace std;

#include "SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

#define ToRadian  0.0174532f
#define PI		  3.1415926f	// 180
#define DIV2PI	  1.5707963f	// 90
#define DIV4PI	  0.7853981f	// 45


#include "GameObject.h"
#include "ObRect.h"
#include "ObStar.h"
#include "ObCircle.h"
#include "ObLine.h"

#include "Types.h"
#include "Input.h"
#include "Timer.h"
#include "MainGame.h"

#define INPUT Input::GetInstance()
#define TIMER Timer::GetInstance()
#define DELTA Timer::GetInstance()->GetDeltaTime()


extern HINSTANCE	g_hInst;
extern HWND			g_hwnd;
extern Scene*		mg;
extern HDC			g_hdc;
extern HDC			g_MemDC;