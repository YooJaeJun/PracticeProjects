#pragma once

template<typename T>
class RBTree
{
public:
	struct Node;
	enum class Color { Red, Black };

public:
	void RotateRight(Node** root, Node* parent)
	{
		Node* leftChild = parent->Left;
		parent->Left = leftChild->Right;

		if (leftChild->Right != nil)
			leftChild->Right->Parent = parent;

		leftChild->Parent = parent->Parent;
		if (parent->Parent != NULL)
		{
			if (parent == parent->Parent->Left)
				parent->Parent->Left = leftChild;
			else
				parent->Parent->Right = leftChild;
		}
		else
		{
			(*root) = leftChild;
		}

		leftChild->Right = parent;
		parent->Parent = leftChild;
	}

	void RotateLeft(Node** root, Node* parent)
	{
		Node* rightChild = parent->Right;
		parent->Right = rightChild->Left;

		if (rightChild->Left != nil)
			rightChild->Left->Parent = parent;

		rightChild->Parent = parent->Parent;
		if (parent->Parent != NULL)
		{
			if (parent == parent->Parent->Left)
				parent->Parent->Left = rightChild;
			else
				parent->Parent->Right = rightChild;
		}
		else
		{
			(*root) = rightChild;
		}

		rightChild->Left = parent;
		parent->Parent = rightChild;
	}

	void InsertNode(Node** node, Node* newNode)
	{
		InsertNodeInternal(node, newNode);

		newNode->Color = Color::Red;
		newNode->Left = nil;
		newNode->Right = nil;

		RebuildInsert(node, newNode);
	}

	void RebuildInsert(Node** root, Node* node)
	{
		while (node != (*root) && node->Parent->Color == Color::Red) // 4번 규칙을 위반한다고 간주
		{
			if (node->Parent == node->Parent->Parent->Left) // 부모 노드가 할아버지의 왼쪽
			{
				Node* uncle = node->Parent->Parent->Right;

				if (uncle->Color == Color::Red) // 삼촌이 빨간색일 때 
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else
				{
					if (node == node->Parent->Right) // 삼촌이 검은색이고, node가 오른쪽 자식
					{
						node = node->Parent;
						RotateLeft(root, node);
					}

					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					RotateRight(root, node->Parent->Parent);
				}
			}
			else
			{
				Node* uncle = node->Parent->Parent->Left;

				if (uncle->Color == Color::Red)
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else
				{
					if (node == node->Parent->Left) //
					{
						node = node->Parent;
						RotateRight(root, node);
					}

					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					RotateLeft(root, node->Parent->Parent);
				}
			}//if(node->parent)
		}//while(node)

		(*root)->Color = Color::Black;
	}


	Node* RemoveNode(Node** root, T data)
	{
		Node* target = Search(*root, data);
		if (target == NULL) return NULL;

		Node* remove = NULL;
		if (target->Left == nil || target->Right == nil)
		{
			remove = target;
		}
		else
		{
			remove = SearchMinNode(target->Right);
			target->Data = remove->Data;
		}

		Node* successor = NULL;
		if (remove->Left != nil)
			successor = remove->Left;
		else
			successor = remove->Right;

		successor->Parent = remove->Parent;

		if (remove->Parent != NULL)
		{
			if (remove == remove->Parent->Left)
				remove->Parent->Left = successor;
			else
				remove->Parent->Right = successor;
		}
		else
		{
			(*root) = successor;
		}

		if (remove->Color == Color::Black)
		{
			RebuildRemove(root, successor);
		}

		return remove;
	}

	void RebuildRemove(Node** root, Node* node)
	{
		Node* sibling = NULL;

		while (node->Parent != NULL && node->Color == Color::Black)
		{
			if (node == node->Parent->Left)
			{
				sibling = node->Parent->Right;

				if (sibling->Color == Color::Red)
				{
					sibling->Color = Color::Black;
					node->Parent->Color = Color::Red;

					RotateLeft(root, node->Parent);
				}
				else
				{
					if (sibling->Left->Color == Color::Black && sibling->Right->Color == Color::Black)
					{
						sibling->Color = Color::Red;
						node = node->Parent;
					}
					else
					{
						if (sibling->Left->Color == Color::Red)
						{
							sibling->Left->Color = Color::Black;
							sibling->Color = Color::Red;

							RotateRight(root, sibling);
							sibling = node->Parent->Right;
						}

						sibling->Color = node->Parent->Color;
						node->Parent->Color = Color::Black;
						sibling->Right->Color = Color::Black;

						RotateLeft(root, node->Parent);
						node = (*root);
					}
				}
			}
			else
			{
				sibling = node->Parent->Left;

				if (sibling->Color == Color::Red)
				{
					sibling->Color = Color::Black;
					node->Parent->Color = Color::Red;

					RotateRight(root, node->Parent);
				}
				else
				{
					if (sibling->Right->Color == Color::Black && sibling->Left->Color == Color::Black)
					{
						sibling->Color = Color::Red;
						node = node->Parent;
					}
					else
					{
						if (sibling->Right->Color == Color::Red)
						{
							sibling->Right->Color = Color::Black;
							sibling->Color = Color::Red;

							RotateLeft(root, sibling);
							sibling = node->Parent->Left;
						}

						sibling->Color = node->Parent->Color;
						node->Parent->Color = Color::Black;
						sibling->Left->Color = Color::Black;

						RotateRight(root, node->Parent);
						node = (*root);
					}
				}
			}
		}

		node->Color = Color::Black;
	}


private:
	void InsertNodeInternal(Node** node, Node* newNode)
	{
		if (*node == NULL)
			*node = newNode;

		if ((*node)->Data < newNode->Data)
		{
			if ((*node)->Right == nil)
			{
				(*node)->Right = newNode;
				newNode->Parent = *node;
			}
			else
				InsertNodeInternal(&(*node)->Right, newNode);
		}
		else if ((*node)->Data > newNode->Data)
		{
			if ((*node)->Left == nil)
			{
				(*node)->Left = newNode;
				newNode->Parent = *node;
			}
			else
				InsertNodeInternal(&(*node)->Left, newNode);
		}
	}

public:
	struct Node
	{
		Node* Parent;
		Node* Left;
		Node* Right;
		Color Color;

		T Data;
	};

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Parent = NULL;
		node->Left = node->Right = NULL;
		node->Color = Color::Black;
		node->Data = data;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = NULL;
	}

private:
	Node* nil;
};