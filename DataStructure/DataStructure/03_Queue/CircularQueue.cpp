#include <stdio.h>
#include "CircularQueue.h"

int main()
{
	Queue<int> queue(10);
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	queue.Enqueue(4);

	for (int i = 0; i < 3; i++)
	{
		printf("Dequeue: %d, ", queue.Dequeue());
		printf("Front: %d, Rear: %d\n", queue.Front(), queue.Rear());
	}

	int count = 100;
	while (queue.IsFull() == false)
		queue.Enqueue(count++);

	printf("Capacity: %d, ", queue.Capacity());
	printf("Front: %d, Rear: %d\n", queue.Front(), queue.Rear());


	while (queue.IsEmpty() == false)
	{
		printf("Dequeue: %d, ", queue.Dequeue());
		printf("Front: %d, Rear: %d\n", queue.Front(), queue.Rear());
	}

	return 0;
}