#pragma once
#include <iostream>

template<typename T>
class MyBTree
{
public:
	struct Node
	{
		T data;
		Node* left = nullptr;
		Node* right = nullptr;

		Node() = default;
		Node(T value)
			: data(value), left(nullptr), right(nullptr)
		{}
	};

public:
	MyBTree() = default;
	MyBTree(Node* node)
		: root(node)
	{}
	
	~MyBTree()
	{
		Destroy(root);
	}

	void Destroy(Node* node)
	{
		if (node == nullptr)
			return;

		Destroy(node->left);
		Destroy(node->right);

		DestroyNode(&node);
	}

	void PreOrder(Node* node)
	{
		if (node == nullptr)
			return;
		
		std::cout << node->data << ' ';
		PreOrder(node->left);
		PreOrder(node->right);
	}

	void InOrder(Node* node)
	{
		if (node == nullptr)
			return;

		InOrder(node->left);
		std::cout << node->data << ' ';
		InOrder(node->right);
	}

	void PostOrder(Node* node)
	{
		if (node == nullptr)
			return; 

		PostOrder(node->left);
		PostOrder(node->right);
		std::cout << node->data << ' ';
	}

	Node* Root() { return root; }

public:
	static Node* CreateNode(T value)
	{
		Node* node = new Node(value);
		return node;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = nullptr;
	}

private:
	Node* root;
};