#pragma once
#include <iostream>
#include <cassert>

/// <summary>
/// LinkedList
/// </summary>
template<typename T>
class MyQueueByLinkedList
{
public:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	static Node* Create(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = NULL;
		return newNode;
	}

	static void Destroy(Node** node)
	{
		delete *node;
		*node = nullptr;
	}

	MyQueueByLinkedList()
	{}

	~MyQueueByLinkedList()
	{
		while (IsEmpty() == false)
		{
			Node* node = Dequeue();
			Destroy(&node);
		}
	}

	void Enqueue(Node* node)
	{
		if (IsEmpty())
		{
			front = rear = node;
		}
		else
		{
			rear->next = node;
			rear = node;
		}

		size++;
	}

	Node* Dequeue()
	{
		Node* node = front;

		if (front->next == nullptr)
			front = rear = nullptr;
		else
			front = front->next;

		size--;

		return node;
	}

	bool IsEmpty() const
	{
		return front == nullptr;
	}

	int Size() const { return size; }
	Node* Front() const { return front; }
	Node* Rear() const { return rear; }

private:
	int size = 0;
	Node* front;
	Node* rear;
};


/// <summary>
/// Dynamic Array
/// </summary>
template<typename T>
class MyQueue
{
public:
	MyQueue(int capacity)
		: capacity(capacity)
	{
		data = new T[capacity];
	}

	~MyQueue()
	{
		delete[] data;
		data = nullptr;
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		if (front < rear)
			return rear - front + 1 == capacity;
		else
			return rear + 1 == front;
	}

	void Enqueue(T value)
	{
		assert(IsFull() == false);

		rear = (rear + 1) % capacity;
		data[rear] = value;

		size++;
	}

	T Dequeue()
	{
		assert(IsEmpty() == false);

		front = (front + 1) % capacity;
		T ret = data[front];
		data[front] = 0;

		size--;

		return ret;
	}

	void Print() const
	{
		for (int i = front; i < rear; i++)
		{
			std::cout << data[i] << ' ';
		}
		std::cout << std::endl;
	}

	int Capacity() const { return capacity; }
	int Size() const { return size; }
	int Front() const { return front; }
	int Rear() const { return rear; }

private:
	T* data;
	int capacity = 0;
	int size = 0;
	int front = 0;
	int rear = 0;
};

