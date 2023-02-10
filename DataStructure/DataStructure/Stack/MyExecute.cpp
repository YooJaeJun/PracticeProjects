#include "MyStack.h"
using namespace std;

//
// Array
//

//int main()
//{
//	MyStackByArray<string> stack = MyStackByArray<string>::Create("abc");
//	stack.Push("abc");
//	stack.Push("bcd");
//	stack.Push("cde");
//	stack.Push("def");
//
//	int count = stack.Size();
//	printf("Size: %d\n", count);
//
//	for (int i = 0; i < count; i++)
//	{
//		if (stack.IsEmpty() == true)
//			break;
//
//		string temp = stack.Pop();
//		printf("pop : %s\n", temp.c_str());
//
//		if (stack.IsEmpty() == false)
//			printf("Top : %s\n", stack.Top().c_str());
//		else
//			printf("스택 비었음둥!\n");
//	}
//
//	return 0;
//}


//
// LinkedList
//
int main()
{
	MyStackByLinkedList<string> stack;
 	stack.Push(MyStackByLinkedList<string>::Create("abc"));
	//stack.Push(MyStackByLinkedList<string>::Create("bcd"));
	//stack.Push(MyStackByLinkedList<string>::Create("cde"));
	//stack.Push(MyStackByLinkedList<string>::Create("def"));

	int count = stack.Size();
	printf("Size: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		if (stack.IsEmpty() == true)
			break;

		string temp = stack.Pop()->value;
		printf("pop : %s\n", temp.c_str());

		if (stack.IsEmpty() == false)
			printf("Top : %s\n", stack.Top()->value.c_str());
		else
			printf("스택 비었음둥!\n");
	}

	_CrtDumpMemoryLeaks();

	return 0;
}