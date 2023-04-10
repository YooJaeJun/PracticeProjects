#pragma once
#include "Systems/IExecute.h"

class ThreadDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override {}
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private:
	void Loop();

	void Function();
	
	void MultiThread();
	void MultiThread1();
	void MultiThread2();

	void Join();

	void Mutex();
	void MutexUpdate();

	void RaceCondition(int& counter);
	void Execute();

	void ExecuteTimer();
	void ExecutePerfomence();

private:
	mutex m;
	float progress = 0.0f;

	Timer timer;
	Timer timer2;
};