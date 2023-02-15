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

	return 0;
}