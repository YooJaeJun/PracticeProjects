#pragma once
#include <stdio.h>
#include <iostream>

template<typename T>
class BTree
{
public:
	struct Node;

public:
	BTree()
	{

	}

	~BTree()
	{
		Destroy(root);
	}

public:
	void PreOrder(Node* node)
	{
		if (node == NULL)
			return;

		std::cout << ' ' << node->data;

		PreOrder(node->left);
		PreOrder(node->right);
	}

	void InOrder(Node* node)
	{
		if (node == NULL)
			return;

		InOrder(node->left);

		std::cout << ' ' << node->data;

		InOrder(node->right);
	}

	void PostOrder(Node* node)
	{
		if (node == NULL)
			return;

		PostOrder(node->left);
		PostOrder(node->right);

		std::cout << ' ' << node->data;
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->data = data;
		node->left = node->right = NULL;

		return node;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = nullptr;
	}

private:
	void Destroy(Node* node)
	{
		if (node == NULL)
			return;

		Destroy(node->left);
		Destroy(node->right);

		DestroyNode(&node);
	}

public:
	void Root(Node* node) { root = node; }

public:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
	};

private:
	Node* root;
};

