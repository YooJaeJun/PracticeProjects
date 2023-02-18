#include <string>
#include "BTree.h"
using namespace std;

void Expression(const char* postfix, BTree<char>::Node** node)
{
	char* str = const_cast<char*>(postfix);	// const_cast 쓰지 말 것

	size_t length = strlen(str);
	char tocken = str[length - 1];
	str[length - 1] = '\0';
	
	switch (tocken)
	{
		case '+': case '-': case '*': case '/': case '%':
		{
			*node = BTree<char>::CreateNode(tocken);

			Expression(postfix, &(*node)->right);
			Expression(postfix, &(*node)->left);
		}
		break;

		default:
		{
			*node = BTree<char>::CreateNode(tocken);
		}//case
	}//swith
}

float Evaluate(BTree<char>::Node* node)
{
	if (node == NULL)
		return 0.0f;

	switch (node->data)
	{
		case '+': case '-': case '*': case '/': case '%':
		{
			float left = Evaluate(node->left);
			float right = Evaluate(node->right);

			// TODO: 연산
			switch (node->data)
			{
				case '+': return left + right;
				case '-': return left - right;
				case '*': return left * right;
				case '/': return left / right;
				case '%': return (int)left % (int)right;
			}
		}
		break;

		default:
		{
			char temp[4];
			memset(temp, 0, sizeof(temp));

			temp[0] = node->data;

			return atof(temp);
		}
		break;
	}

	return 0.0f;
}

int main()
{
	BTree<char>::Node* root = NULL;

	string postfix = "34*12+32/+-";
	Expression(postfix.c_str(), &root);

	BTree<char> tree;
	tree.Root(root);

	cout << "-- Pre Order--" << endl;
	tree.PreOrder(root);

	cout << endl << endl << "-- In Order--" << endl;
	tree.InOrder(root);

	cout << endl << endl << "-- Post Order--" << endl;
	tree.PostOrder(root);

	cout << endl << Evaluate(root) << endl;

	return 0;
}