#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer()
	{
		QueryPerformanceFrequency(&tick);
	}

	void Start()
	{
		QueryPerformanceCounter(&start);
	}

	void End()
	{
		QueryPerformanceCounter(&end);
	}
	
	float RunningTime()
	{
		__int64 elapsed = end.QuadPart - start.QuadPart;
		return (float)((double)elapsed / (double)tick.QuadPart * 1000.0);
	}

private:
	LARGE_INTEGER tick;
	LARGE_INTEGER start, end;
};
