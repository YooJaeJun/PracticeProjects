#pragma once

#include <memory>
#include <assert.h>

#define MAX_STACK_COUNT 20

template<typename T>
class Stack
{
public:
	Stack()
	{
		memset(values, 0, sizeof(T) * MAX_STACK_COUNT);
	}

	void Push(T value)
	{
		assert(top + 1 < MAX_STACK_COUNT);

		values[++top] = value;
	}

	T Pop()
	{
		assert(Empty() == false);

		T val = values[top--];

		return val;
	}

	T Front()
	{
		return values[top];
	}

	T Back()
	{
		assert(top > -1);

		return values[0];
	}

	bool Empty()
	{
		return top < 0;
	}

	
private:
	int top = -1;

	T values[MAX_STACK_COUNT];
};

