#include <stdio.h>
#include "StackByLinkedList.h"

int main()
{
	StackByLinkedList stack;
	stack.Push(StackByLinkedList::CreateNode("abc"));
	stack.Push(StackByLinkedList::CreateNode("bcd"));
	stack.Push(StackByLinkedList::CreateNode("cde"));
	stack.Push(StackByLinkedList::CreateNode("def"));

	int count = stack.Size();
	printf("Size: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		if (stack.IsEmpty() == true)
			break;

		Node* temp = stack.Pop();
		printf("pop : %s\n", temp->Data.c_str());
		StackByLinkedList::DestroyNode(&temp);

		if (stack.IsEmpty() == false)
			printf("Top : %s\n", stack.Top()->Data.c_str());
		else
			printf("스택 비었음둥!\n");
	}

	return 0;
}