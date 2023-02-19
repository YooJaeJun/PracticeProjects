#pragma once

template<typename T>
class BinarySearchTree
{
public:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
	};

public:
	BinarySearchTree()
	{}
	~BinarySearchTree()
	{
	}

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
	}

	Node* Search(Node* node, T data, int& depth)
	{
		if (node == nullptr)
			return nullptr;

		depth++;

		if (node->data == data)
			return node;
		else if (node->data > data)
			return Search(node->left, data, depth);
		else if (node->data < data)
			return Search(node->right, data, depth);

		return nullptr;
	}

	void InOrder(Node* node, int depth)
	{
		if (node == nullptr)
			return;

		depth++;

		InOrder(node->left, depth);

		std::cout << " " << node->data << "|" << depth << std::endl;

		InOrder(node->right, depth);
	}

	Node* Remove(Node* node, Node* parent, T data)
	{
		Node* remove = NULL;
		if (node == NULL)
			return NULL;

		if (node->data > data)
			remove = Remove(node->left, node, data);
		else if (node->data < data)
			remove = Remove(node->right, node, data);
		else // 탐색완료. 노드삭제
		{
			remove = node;

			if (node->left == NULL && node->right == NULL)
			{
				if (parent->left == node)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			else
			{
				if (node->left != NULL && node->right != NULL)	// 양쪽 모두 존재
				{
					Node* minNode = SearchMinValue(node->right);

					minNode = Remove(node, NULL, minNode->data);
					node->data = minNode->data;

					return minNode;
				}
				else  // 한쪽만 존재
				{
					Node* temp = NULL;

					if (node->left != NULL)
						temp = node->left;
					else
						temp = node->right;

					if (parent->left == node)
						parent->left = temp;
					else
						parent->right = temp;
				}
			}//if(node->left)
		}//if(node->data)

		return remove;
	}

	Node* SearchMinValue(Node* node)
	{
		if (node == NULL)
			return NULL;

		if (node->left == NULL)
			return node;
		else
			return SearchMinValue(node->left);
	}

	Node* Root() 
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
		Node* node = new Node();
		node->data = data;
		node->left = node->right = NULL;

		return node;
	}

	static void DestroyNode(Node** node)
	{
		delete* node;
		*node = NULL;
	}

private:
	Node* root;
};

