#pragma once

class Timer : public Singleton<Timer>
{
private:
	// ���� �����ð�
	chrono::steady_clock::time_point CurrentTime;
	// ������ �����ð�
	chrono::steady_clock::time_point LastTime;

	// �����Ӵ� ����ð�
	float deltaTime;

	// ������ Ȯ�ο� ����
	UINT FPS;
	float WorldTime;

	// FPS ������ ����
	UINT FPSCount;
	float FPSTimeElapsed;

public:
	Timer();
	void Chronometry(UINT lock = 60);
	float GetDeltaTime() { return deltaTime; }
	UINT GetFPS() { return FPS; }
	float GetWorldTime() { return WorldTime; }
};
