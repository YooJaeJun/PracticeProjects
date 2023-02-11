#pragma once
#include <stdio.h>

template<typename T>
class Queue
{
public:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	Queue()
	{
	}

	~Queue()
	{
		while (IsEmpty() == false)
		{
			Node* node = Dequeue();
			Destroy(&node);
		}
	}

	void Enqueue(Node* node)
	{
		if (front == NULL)
		{
			front = node;
			rear = node;

			count++;

			return;
		}

		rear->next = node;
		rear = node;

		count++;
	}

	Node* Dequeue()
	{
		Node* node = front;

		if (front->next == NULL)
			front = rear = NULL;
		else
			front = front->next;

		count--;

		return node;
	}

	int Size() { return count; }

	bool IsEmpty()
	{
		return front == NULL;
	}

public:
	static Node* Create(T data)
	{
		Node* node = new Node();
		node->data = data;
		node->next = NULL;

		return node;
	}

	static void Destroy(Node** node)
	{
		delete* node;
		*node = NULL;
	}

private:
	int count = 0;
	Node* front = NULL;
	Node* rear = NULL;
};

