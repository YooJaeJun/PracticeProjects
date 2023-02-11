#include "QueueByLinkedList.h"

int main()
{
	Queue<int> queue;
	queue.Enqueue(Queue<int>::Create(10));
	queue.Enqueue(Queue<int>::Create(20));
	queue.Enqueue(Queue<int>::Create(30));

	printf("Size: %d\n", queue.Size());

	while (queue.IsEmpty() == false)
	{
		Queue<int>::Node* node = queue.Dequeue();
		printf("Dequeue : %d\n", node->data);

		Queue<int>::Destroy(&node);
	}

	return 0;
}