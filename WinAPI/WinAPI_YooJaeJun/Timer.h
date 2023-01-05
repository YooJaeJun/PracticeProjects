#pragma once

class Timer : public Singleton<Timer>
{
private:
	// 현재 측정시간
	chrono::steady_clock::time_point CurrentTime;
	// 지난번 측정시간
	chrono::steady_clock::time_point LastTime;

	// 프레임당 경과시간
	float deltaTime;

	// 측정값 확인용 변수
	UINT FPS;
	float WorldTime;

	// FPS 측정용 변수
	UINT FPSCount;
	float FPSTimeElapsed;

public:
	Timer();
	void Chronometry(UINT lock = 60);
	float GetDeltaTime() { return deltaTime; }
	UINT GetFPS() { return FPS; }
	float GetWorldTime() { return WorldTime; }
};
