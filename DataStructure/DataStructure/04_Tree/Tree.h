#pragma once
#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
class Tree
{
public:
	struct Node;

public:
	void AddChild(Node* parent, Node* child)
	{
		if (parent->leftChild == NULL)
		{
			parent->leftChild = child;

			return;
		}

		Node* node = parent->leftChild;
		while (node->rightSibling != NULL)
			node = node->rightSibling;

		node->rightSibling = child;
	}

	void PrintNode(Node* node, int depth)
	{
		for (int i = 0; i < depth; i++)
			cout << "-";

		cout << node->data << endl;
		stack.push(node);
		queue.push(node);

		if (node->leftChild != NULL)
			PrintNode(node->leftChild, depth + 1);

		if (node->rightSibling != NULL)
			PrintNode(node->rightSibling, depth);
		
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->data = data;
		node->leftChild = node->rightSibling = NULL;

		return node;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = NULL;
	}

public:
	stack<Node*>* Stack() { return &stack; }
	queue<Node*>* Queue() { return &queue; }

public:
	struct Node
	{
		T data;
		Node* leftChild;
		Node* rightSibling;

		~Node()
		{
			data = 0;
			leftChild = NULL;
			rightSibling = NULL;
		}
	};

private:
	stack<Node*> stack;
	queue<Node*> queue;
};

