#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int global = 0;
mutex m;

void Plus()
{
	for (int i = 0; i < 1000; i++)
	{
		m.lock();
		global = global + 1;
		m.unlock();
	}
}

int main()
{
	thread* t[10];

	for (int i = 0; i < 10; i++)
	{
		t[i] = new thread(Plus);
	}

	for (int i = 0; i < 10; i++)
	{
		t[i]->join();
	}

	cout << global << endl;
}