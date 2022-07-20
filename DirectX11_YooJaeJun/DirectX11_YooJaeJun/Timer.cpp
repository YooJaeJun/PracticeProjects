#include "framework.h"

Timer::Timer()
{
	// 현재 시간 측정
	LastTime = chrono::steady_clock::now();

	deltaTime = 0.0f;
	WorldTime = 0.0f;
	FPS = 0;
	FPSCount = 0;
	FPSTimeElapsed = 0.0f;
}

void Timer::Chronometry(UINT lock)
{
	CurrentTime = chrono::steady_clock::now();
	// 지난시간 - 현재시간값을 나노 초단위로 받기
	chrono::duration<double> Delta = CurrentTime - LastTime;
	// 초단위로 변경하여 값 받기
	deltaTime = (float)Delta.count();

	// 델타가 1/60보다 작다면
	while (deltaTime < (1.0f / lock))
	{
		// 현재시간을 다시 측정
		CurrentTime = chrono::steady_clock::now();
		// 델타를 다시 계산
		Delta = CurrentTime - LastTime;
		deltaTime = (float)Delta.count();
	}


	LastTime = CurrentTime;

	WorldTime += deltaTime;

	FPSTimeElapsed += deltaTime;

	FPSCount++;

	// FPSTimeElapsed 이 1초가 넘었을 때
	if (FPSTimeElapsed > 1.0f)
	{
		FPS = FPSCount;
		FPSCount = 0;
		FPSTimeElapsed = 0.0f;
	}

}