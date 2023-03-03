#include "stdafx.h"
#include "ThreadDemo.h"

void ThreadDemo::Initialize()
{
	//Loop();

	//function<void()> f = bind(&ThreadDemo::Function, this);
	//f();

	//MultiThread();

	Join();
}

void ThreadDemo::Update()
{

}

void ThreadDemo::Render()
{
	
}

void ThreadDemo::Loop()
{
	for (int i = 0; i < 100; i++)
		printf("1 : %d\n", i);
	printf("반복문1 종료\n");

	for (int i = 0; i < 100; i++)
		printf("2 : %d\n", i);
	printf("반복문2 종료\n");
}

void ThreadDemo::Function()
{
	printf("함수 포인터 호출\n");
}

void ThreadDemo::MultiThread()
{
	thread t(bind(&ThreadDemo::MultiThread1, this));
	thread t2(bind(&ThreadDemo::MultiThread2, this));

	t2.join();
	printf("t2.join\n");

	t.join();
	printf("t.join\n");
}

void ThreadDemo::MultiThread1()
{
	for (int i = 0; i < 100; i++)
		printf("1 : %d\n", i);
	printf("반복문1 종료\n");
}

void ThreadDemo::MultiThread2()
{
	for (int i = 0; i < 100; i++)
		printf("2 : %d\n", i);
	printf("반복문2 종료\n");
}

void ThreadDemo::Join()
{
	thread t([]()
	{
		for (int i = 0; i < 100; i++)
			printf("1 : %d\n", i);
		printf("반복문1 종료\n");
	});

	thread t2([]()
	{
		int a = 0;
		while (true)
		{
			a++;
			printf("A : %d\n", a);

			Sleep(100);

			if (a > 30)
				break;
		}
	});

	printf("멀티 쓰레드 시작\n");

	t2.join();
	printf("t2 join\n");

	t.join();
	printf("t.join\n");
}
