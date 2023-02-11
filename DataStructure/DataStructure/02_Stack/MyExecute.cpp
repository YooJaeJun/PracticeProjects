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
void Solution()
{
	MyStackByLinkedList<string> stack;
	Node<string>* newNode = new Node<string>("abc");
	Node<string>* newNode2 = new Node<string>("bcd");
	stack.Push(newNode);
	stack.Push(newNode2);
	//stack.Push(MyStackByLinkedList<string>::Create("cde"));
	//stack.Push(MyStackByLinkedList<string>::Create("def"));

	int count = stack.Size();
	printf("Size: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		if (stack.IsEmpty() == true)
			break;

		Node<string>* temp = stack.Pop();
		printf("pop : %s\n", temp->value.c_str());

		if (stack.IsEmpty() == false)
			printf("Top : %s\n", stack.Top()->value.c_str());
		else
			printf("스택 비었음둥!\n");

		delete temp;
	}
}

int main()
{
	Solution();
	_CrtDumpMemoryLeaks();
	return 0;
}