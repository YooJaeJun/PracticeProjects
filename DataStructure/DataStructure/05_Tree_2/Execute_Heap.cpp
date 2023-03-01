#include "Heap.h"

int main()
{
	Heap<int> heap(3);

	heap.Insert(12);
	heap.Insert(88);
	heap.Insert(43);
	heap.Insert(17);
	heap.Insert(161);
	heap.Insert(67);
	heap.Insert(8);
	heap.Insert(13);
	heap.Insert(52);
	heap.Insert(7);
	heap.Insert(2);

	heap.Print();

	while (heap.Empty() == false)
	{
		heap.RemoveMin();
		heap.Print();
	}

	return 0;
}