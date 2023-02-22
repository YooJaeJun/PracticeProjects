#pragma once

template <typename T>
class MyBinarySearchTree
{
public:
	struct Node
	{
		Node() : data(0), left(nullptr), right(nullptr) {}
		Node(T data) : data(data), left(nullptr), right(nullptr) {}
		T data;
		Node* left;
		Node* right;
	};

public:
	void Insert(Node** parent, Node* child)
	{
		if ((*parent)->data < child->data)
		{
			if ((*parent)->right == nullptr)
				(*parent)->right = child;
			else
				Insert(&(*parent)->right, child);
		}
		else if ((*parent)->data > child->data)
		{
			if ((*parent)->left == nullptr)
				(*parent)->left = child;
			else
				Insert(&(*parent)->left, child);
		}
		// 중복 입력은 없다고 가정
	}

	Node* Search(Node* node, T data, int& depth)
	{
		if (node == nullptr)
			return nullptr;

		depth++;

		if (node->data == data)
			return node;
		else if (node->data < data)
			return Search(node->right, data, depth);
		else
			return Search(node->left, data, depth);

		return nullptr;
	}

	void InOrder(Node* node, int depth)
	{
		if (node == nullptr)
			return;

		InOrder(node->left, depth + 1);

		std::cout << node->data << "  " << depth << std::endl;

		InOrder(node->right, depth + 1);
	}

	Node* SearchMinNode(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->left)
			return SearchMinNode(node->left);
		else
			return node;
	}

	Node* Remove(Node* node, Node* parent, T data)
	{
		Node* remove = nullptr;

		if (node == nullptr)
			return nullptr;

		if (node->data > data)
			remove = Remove(node->left, node, data);
		else if (node->data < data)
			remove = Remove(node->right, node, data);
		else
		{
			remove = node;

			if (node->left == nullptr && node->right == nullptr)
			{
				if (parent->left == node)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}
			else if (node->left && node->right)
			{
				Node* minNode = SearchMinNode(node->right);

				minNode = Remove(node, nullptr, minNode->data);
				node->data = minNode->data;

				return minNode;
			}
			else
			{
				Node* temp = nullptr;

				// 노드 올라오기
				if (node->left)
					temp = node->left;
				else
					temp = node->right;

				if (parent->left == node)
					parent->left = temp;
				else
					parent->right = temp;
			}
		}

		return remove;
	}


	Node* Root() const 
	{ 
		return root; 
	}

	void SetRoot(Node* root)
	{
		this->root = root;
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
	Node* root;
};

