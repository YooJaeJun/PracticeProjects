#pragma once
#include <iostream>

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

	int Parent(int index)
	{
		return (int)((index - 1) / 2);
	}

	int LeftChild(int index)
	{
		return index * 2 + 1;
	}

	void SwapNode(int index1, int index2)
	{
		Node* temp = new Node();
		memcpy(temp, &nodes[index1], sizeof(Node));
		memcpy(&nodes[index1], &nodes[index2], sizeof(Node));
		memcpy(&nodes[index2], temp, sizeof(Node));

		delete temp;
	}

	void Insert(Node data)
	{
		int current = size;
		int parent = Parent(current);

		if (size == capacity)
		{
			Node* temp = new Node[capacity * 2];
			memcpy(temp, nodes, sizeof(Node) * capacity);

			delete[] nodes;
			nodes = temp;

			capacity *= 2;
		}

		nodes[current] = data;

		while (current > 0 && nodes[current].data < nodes[parent].data)
		{
			SwapNode(current, parent);

			current = parent;
			parent = Parent(current);
		}

		size++;
	}

	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			int parent = -1;
			if (i > 0)
				parent = Parent(i);

			std::cout << nodes[i].data << "|" << parent << ", ";
		}

		std::cout << "\n\n";
	}

	Node RemoveMin()
	{
		int parent = 0;
		int left = 0;
		int right = 0;

		Node result;
		memcpy(&result, &nodes[0], sizeof(Node));

		size--;
		SwapNode(0, size);

		left = LeftChild(0);
		right = left + 1;

		while (true)
		{
			int selected = 0;
			
			if (left >= size)
				break;

			if (right >= size)
			{
				selected = left;
			}
			else
			{
				if (nodes[left].data > nodes[right].data)
					selected = right;
				else
					selected = left;
			}

			if (nodes[selected].data < nodes[parent].data)
			{
				SwapNode(parent, selected);

				parent = selected;
			}
			else
				break;

			left = LeftChild(parent);
			right = left + 1;
		}

		return result;
	}

	bool Empty() { return size == 0; }


public:
	struct Node
	{
		T data;

		Node() {}
		Node(T data) : data(data)
		{}
	};

private:
	Node* nodes;

	int capacity;
	int size;
};

