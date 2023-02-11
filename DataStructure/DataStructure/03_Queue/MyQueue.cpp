#include "MyQueue.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
using namespace std;

void MyQueueByLinkedListDemo()
{
	MyQueueByLinkedList<int> queue;
	queue.Enqueue(MyQueueByLinkedList<int>::Create(10));
	queue.Enqueue(MyQueueByLinkedList<int>::Create(20));
	queue.Enqueue(MyQueueByLinkedList<int>::Create(30));

	printf("Size: %d\n", queue.Size());

	while (queue.IsEmpty() == false)
	{
		MyQueueByLinkedList<int>::Node* node = queue.Dequeue();
		printf("Dequeue : %d\n", node->data);

		MyQueueByLinkedList<int>::Destroy(&node);
	}
}

void MyQueueDemo()
{
	MyQueue<int> MyQueue(10);
	MyQueue.Enqueue(1);
	MyQueue.Enqueue(2);
	MyQueue.Enqueue(3);
	MyQueue.Enqueue(4);

	for (int i = 0; i < 3; i++)
	{
		printf("DeMyQueue: %d, ", MyQueue.Dequeue());
		printf("Front: %d, Rear: %d\n", MyQueue.Front(), MyQueue.Rear());
	}

	int count = 100;
	while (MyQueue.IsFull() == false)
		MyQueue.Enqueue(count++);

	printf("Capacity: %d, ", MyQueue.Capacity());
	printf("Front: %d, Rear: %d\n", MyQueue.Front(), MyQueue.Rear());


	while (MyQueue.IsEmpty() == false)
	{
		printf("DeMyQueue: %d, ", MyQueue.Dequeue());
		printf("Front: %d, Rear: %d\n", MyQueue.Front(), MyQueue.Rear());
	}

	return;
}

int main()
{
	// MyQueueDemo();
	MyQueueByLinkedListDemo();
	_CrtDumpMemoryLeaks();
	return 0;
}