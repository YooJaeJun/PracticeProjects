#include "framework.h"

Timer::Timer()
{
	// ���� �ð� ����
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
	// �����ð� - ����ð����� ���� �ʴ����� �ޱ�
	chrono::duration<double> Delta = CurrentTime - LastTime;
	// �ʴ����� �����Ͽ� �� �ޱ�
	deltaTime = (float)Delta.count();

	// ��Ÿ�� 1/60���� �۴ٸ�
	while (deltaTime < (1.0f / lock))
	{
		// ����ð��� �ٽ� ����
		CurrentTime = chrono::steady_clock::now();
		// ��Ÿ�� �ٽ� ���
		Delta = CurrentTime - LastTime;
		deltaTime = (float)Delta.count();
	}


	LastTime = CurrentTime;

	WorldTime += deltaTime;

	FPSTimeElapsed += deltaTime;

	FPSCount++;

	// FPSTimeElapsed �� 1�ʰ� �Ѿ��� ��
	if (FPSTimeElapsed > 1.0f)
	{
		FPS = FPSCount;
		FPSCount = 0;
		FPSTimeElapsed = 0.0f;
	}

}