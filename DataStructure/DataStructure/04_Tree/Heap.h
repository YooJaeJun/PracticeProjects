#pragma once

template <typename T>
class Heap
{
public:
	struct Node;

public:
	Heap(int capacity)
		: capacity(capacity)
	{
		nodes = new Node[capacity];
		size = 0;
	}

	~Heap()
	{
		delete[] nodes;
		nodes = nullptr;
	}


public:
	struct Node
	{
		T data;

		Node() {}
		Node(T data) : data(data)
		{}
	}

private:
	Node* nodes;

	int capacity;
	int size;


};

