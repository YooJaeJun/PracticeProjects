#include <stdio.h>
#include "Stack.h"

int main()
{
	Stack<int> stack;
	stack.Push(10);
	stack.Push(20);
	stack.Push(30);
	stack.Pop();

	stack.Push(40);
	stack.Push(50);


	while (stack.Empty() == false)
		printf("%d\n", stack.Pop());


	return 0;
}