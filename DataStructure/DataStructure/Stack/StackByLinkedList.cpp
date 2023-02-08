#include "StackByLinkedList.h"

StackByLinkedList::StackByLinkedList()
{
}

StackByLinkedList::~StackByLinkedList()
{
	while (IsEmpty() == false)
	{
		Node* node = Pop();
		DestroyNode(&node);
	}

	list = NULL;
	top = NULL;
}

void StackByLinkedList::Push(Node* node)
{
	if (list != NULL)
	{
		Node* oldTop = list;
		while (oldTop->NextNode != NULL)
			oldTop = oldTop->NextNode;

		oldTop->NextNode = node;
	}
	else
	{
		list = node;
	}

	top = node;
}

Node* StackByLinkedList::Pop()
{
	Node* temp = top;

	if (list == top)
	{
		list = NULL;
		top = NULL;
	}
	else
	{
		Node* currentTop = list;
		while (currentTop != NULL && currentTop->NextNode != top)
			currentTop = currentTop->NextNode;

		top = currentTop;
		currentTop->NextNode = NULL;
	}

	return temp;
}

int StackByLinkedList::Size()
{
	int count = 0;
	Node* node = list;

	while (node != NULL)
	{
		node = node->NextNode;
		count++;
	}

	return count;
}

Node* StackByLinkedList::CreateNode(string data)
{
	Node* node = new Node();
	node->Data = data;
	node->NextNode = NULL;

	return node;
}

void StackByLinkedList::DestroyNode(Node** node)
{
	delete* node;
	*node = NULL;
}
