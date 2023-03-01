#include "PQueue.h"
using namespace std;

int main()
{
	PQueue<string> queue(12);
	queue.Insert(PQueue<string>::Node(34, "È«±æµ¿"));
	queue.Insert(PQueue<string>::Node(12, "ÀÌ¼ø½Å"));
	queue.Insert(PQueue<string>::Node(87, "¼¼Á¾´ë¿Õ"));
	queue.Insert(PQueue<string>::Node(45, "À»Áö¹®´ö"));
	queue.Insert(PQueue<string>::Node(35, "À¯ÀçÁØ"));
	queue.Insert(PQueue<string>::Node(66, "À¯°ü¼ø"));
	queue.Insert(PQueue<string>::Node(34, "À±ºÀ±æ"));

	queue.Print();

	while (queue.Empty() == false)
	{
		queue.RemoveMin();
		queue.Print();
	}

	return 0;
}