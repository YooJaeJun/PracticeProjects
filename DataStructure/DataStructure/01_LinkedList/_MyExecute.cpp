#include "_MyLinkedList.h"


#include <vector>
using namespace std;

int main()
{
	MyLinkedList<int>* l = MyLinkedList<int>::Create(0);

	l->PushBack(1);
	l->PushBack(2);
	l->PushBack(3);
	l->Print();

	l->PushFront(4);
	l->PushFront(5);
	l->Print();

	l->Remove(2);
	l->Print();
	cout << "비어있니? " << (l->IsEmpty()) << endl;

	l->Clear();
	cout << "비어있니? " << (l->IsEmpty()) << endl;

	Node<int>* ns[3] =
	{
		new Node<int>(0),
		new Node<int>(1),
		new Node<int>(2)
	};
	l->Insert(-1, ns[0]);
	l->Insert(0, ns[1]);
	l->Insert(1, ns[2]);

	l->Print();

	l->Insert(ns[0], (new Node<int>(5)));
	l->Print();

	l->Remove(ns[0]);
	l->Remove(ns[2]);
	l->Print();
}