#pragma once

template<typename T>
class Queue
{
public:
	Queue(int capacity)
		: capacity(capacity)
	{
		datas = new T[capacity + 1];
	}

	~Queue()
	{
		delete[] datas;
		datas = nullptr;
	}

	void Enqueue(T data)
	{
		int position = 0;

		if (rear == capacity)
		{
			position = rear;
			rear = 0;
		}
		else
			position = rear++;

		datas[position] = data;
	}

	T Dequeue()
	{
		int position = front;

		if (front == capacity)
			front = 0;
		else
			front++;

		return datas[position];
	}

	int Size()
	{
		if (front <= rear)
			return rear - front;

		return (capacity - front) + rear + 1;
	}

	bool IsEmpty()
	{
		return front == rear;
	}

	bool IsFull()
	{
		if (front < rear)
			return (rear - front) == capacity;
		else
			return rear + 1 == front;
	}

	int Capacity() { return capacity; }
	int Front() { return front; }
	int Rear() { return rear; }


private:
	T* datas;
	int capacity;
	int front = 0;
	int rear = 0;
};

