#include <windows.h>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

#include "SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

#define ToRadian  0.0174532f
#define PI		  3.1415926f	// 180
#define DIV2PI	  1.5707963f	// 90
#define DIV4PI	  0.7853981f	// 45

#define UP Vector2(0.0f, -1.0f)
#define DOWN Vector2(0.0f, 1.0f)
#define RIGHT Vector2(1.0f, 0.0f)
#define LEFT Vector2(-1.0f, 0.0f)


#include "GameObject.h"
#include "ObRect.h"
#include "ObStar.h"
#include "ObCircle.h"
#include "ObLine.h"

#include "Types.h"
#include "Input.h"
#include "Timer.h"
#include "MainGame.h"

#include "Enemy.h"
#include "Bullet.h"

#define INPUT Input::GetInstance()
#define TIMER Timer::GetInstance()
#define DELTA Timer::GetInstance()->GetDeltaTime()

extern HINSTANCE	g_hInst;
extern HWND			g_hwnd;
extern Scene*		mg;
extern HDC			g_hdc;
extern HDC			g_MemDC;

static float DirToRadian(Vector2 Dir)
{
	// 만약 단위벡터가 아닐 수도 있으니까
	Dir.Normalize();
	float Seta;
	if (Dir.y < 0)
	{
		//	360.0 * ToRadian
		Seta = 2.0f * PI - acosf(Dir.x);
	}
	else
	{
		Seta = acosf(Dir.x);
	}
	return Seta;
}

