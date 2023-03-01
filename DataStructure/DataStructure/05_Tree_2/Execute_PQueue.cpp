#include "PQueue.h"
using namespace std;

int main()
{
	PQueue<string> queue(12);
	queue.Insert(PQueue<string>::Node(34, "ȫ�浿"));
	queue.Insert(PQueue<string>::Node(12, "�̼���"));
	queue.Insert(PQueue<string>::Node(87, "�������"));
	queue.Insert(PQueue<string>::Node(45, "��������"));
	queue.Insert(PQueue<string>::Node(35, "������"));
	queue.Insert(PQueue<string>::Node(66, "������"));
	queue.Insert(PQueue<string>::Node(34, "������"));

	queue.Print();

	while (queue.Empty() == false)
	{
		queue.RemoveMin();
		queue.Print();
	}

	return 0;
}