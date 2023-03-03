#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "MyBTree.h"
using namespace std;

void MyExpression(string& str, MyBTree<char>::Node** node)
{
	char ch = str.back();
	str.pop_back();

	switch (ch)
	{
	case '+': case '-': case '*': case '/': case '%':
	{
		*node = MyBTree<char>::CreateNode(ch);

		MyExpression(str, &(*node)->right);
		MyExpression(str, &(*node)->left);

		break;
	}

	default:
	{
		*node = MyBTree<char>::CreateNode(ch);
		break;
	}
	}
}

void OperatorProcess()
{
	string str = "34*12+32/+-";
	MyBTree<char>::Node* root = nullptr;
	
	MyExpression(str, &root);

	MyBTree<char> tree;

	tree.PreOrder(root);
	cout << endl;
	tree.InOrder(root);
	cout << endl;
	tree.PostOrder(root);
	cout << endl;
}

int main()
{
	OperatorProcess();
	_CrtDumpMemoryLeaks();
	return 0;
}