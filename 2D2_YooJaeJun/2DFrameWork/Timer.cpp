#include "framework.h"

Timer::Timer()
{
    //���� �ð� ����
    lastTime = chrono::steady_clock::now();
    //Ÿ�̸� �����ÿ� ����ð��� �˼�����.
    deltaTime = 0.0f;
    //ó�� ����ð��� 0
    worldTime = 0.0f;
    framePerSecond = 0;
    framePerSecondCount = 0;
    framePerSecondTimeElapsed = 0.0f;
}

bool Timer::GetTick(float& time, float interval)
{
    time += DELTA;
    if (time > interval)
    {
        time -= interval;
        return true;
    }
    return false;
}

void Timer::Chronometry(UINT lock)
{
    currentTime = chrono::steady_clock::now();
    //�����ð� - ����ð����� ���� �ʴ����� �ޱ�
    chrono::duration<double> Delta = currentTime - lastTime;
    //        �ʴ����� �����Ͽ� ���ޱ�
    deltaTime = (float)Delta.count();

    //��Ÿ�� 1/60���� �۴ٸ�
    while (deltaTime < (1.0f / lock))
    {
        //����ð��� �ٽ�����
        currentTime = chrono::steady_clock::now();
        //��Ÿ�� �ٽð��
        Delta = currentTime - lastTime;
        deltaTime = (float)Delta.count();
    }

    //������ �ð��� ���
    lastTime = currentTime;
    //��ü �ð� ������� ����
    worldTime += deltaTime;

    //1�ʸ� ����ִ� ����
    framePerSecondTimeElapsed += deltaTime;

    framePerSecondCount++;
    //FPSTimeElapsed �� 1�ʰ� �Ѿ�����
    if (framePerSecondTimeElapsed > 1.0f)
    {
        framePerSecond = framePerSecondCount;
        framePerSecondCount = 0;
        framePerSecondTimeElapsed = 0.0f;
    }
    deltaScaleTime = deltaTime * app.deltaScale;
}
