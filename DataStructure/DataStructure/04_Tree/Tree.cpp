#include "Tree.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{
	Tree<char> tree;

	Tree<char>::Node* A = Tree<char>::CreateNode('A');
	Tree<char>::Node* B = Tree<char>::CreateNode('B');
	Tree<char>::Node* C = Tree<char>::CreateNode('C');
	Tree<char>::Node* D = Tree<char>::CreateNode('D');
	Tree<char>::Node* E = Tree<char>::CreateNode('E');
	Tree<char>::Node* F = Tree<char>::CreateNode('F');
	Tree<char>::Node* G = Tree<char>::CreateNode('G');
	Tree<char>::Node* H = Tree<char>::CreateNode('H');
	Tree<char>::Node* I = Tree<char>::CreateNode('I');
	Tree<char>::Node* J = Tree<char>::CreateNode('J');
	Tree<char>::Node* K = Tree<char>::CreateNode('K');

	tree.AddChild(A, B);
	tree.AddChild(B, C);
	tree.AddChild(B, D);
	tree.AddChild(D, E);
	tree.AddChild(D, F);

	tree.AddChild(A, G);
	tree.AddChild(G, H);

	tree.AddChild(A, I);
	tree.AddChild(I, J);
	tree.AddChild(I, K);

	tree.PrintNode(A, 0);

	cout << endl << endl;

	while (tree.Queue()->empty() == false)
	{
		cout << tree.Queue()->front()->data << endl;
		tree.Queue()->pop();
	}
	cout << endl << endl;

	while (tree.Stack()->empty() == false)
	{
		Tree<char>::Node* node = tree.Stack()->top();
		cout << node->data << endl;
		tree.Stack()->pop();
		Tree<char>::DestroyNode(&node);
	}
	cout << endl << endl;
	 

	_CrtDumpMemoryLeaks();
	return 0;
}