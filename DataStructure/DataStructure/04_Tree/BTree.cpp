#include "BTree.h"
using namespace std;

int main()
{
	BTree<char> tree;
	BTree<char>::Node* A = tree.CreateNode('A');
	BTree<char>::Node* B = tree.CreateNode('B');
	BTree<char>::Node* C = tree.CreateNode('C');
	BTree<char>::Node* D = tree.CreateNode('D');
	BTree<char>::Node* E = tree.CreateNode('E');
	BTree<char>::Node* F = tree.CreateNode('F');
	BTree<char>::Node* G = tree.CreateNode('G');

	tree.Root(A);
	A->left = B;

	B->left = C;
	B->right = D;

	A->right = E;
	E->left = F;
	E->right = G;

	cout << endl << "-- Pre Order --" << endl;
	tree.PreOrder(A);

	cout << endl << "-- In Order --" << endl;
	tree.InOrder(A);

	cout << endl << "-- Post Order --" << endl;
	tree.PostOrder(A);

	return 0;
}
