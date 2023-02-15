#pragma once
#include <iostream>
#include <stack>
#include <queue>

template<typename T>
class MyTree
{
public:
	struct Node
	{
		T data;
		Node* leftChild = nullptr;
		Node* rightSibling = nullptr;

		Node() = default;
		Node(T value)
			: data(value), leftChild(nullptr), rightSibling(nullptr)
		{}
		
		~Node()
		{
			leftChild = nullptr;
			rightSibling = nullptr;
		}
	};

public:
	void AddChild(Node* parent, Node* child)
	{
		if (parent->leftChild == nullptr)
		{
			parent->leftChild = child;
			return;
		}

		Node* node = parent->leftChild;
		while (node->rightSibling)
		{
			node = node->rightSibling;
		}
		node->rightSibling = child;
	}

	void PrintNode(Node* node, int depth)
	{
		for (int i = 0; i < depth; i++)
			std::cout << '-';

		std::cout << node->data << '\n';

		if (node->leftChild)
			PrintNode(node->leftChild, depth + 1);

		if (node->rightSibling)
			PrintNode(node->rightSibling, depth);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* newNode = new Node(data);
		return newNode;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = nullptr;
	}

private:
	Node* node;
	std::stack<Node*> st;
	std::queue<Node*> qu;
};

