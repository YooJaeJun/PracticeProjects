#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "MyBTree.h"
#include "MyTree.h"
using namespace std;

void BTreeProcess()
{
	MyBTree<char>::Node* A = new MyBTree<char>::Node('A');
	MyBTree<char> tree(A);

	MyBTree<char>::Node* B = new MyBTree<char>::Node('B');
	MyBTree<char>::Node* C = new MyBTree<char>::Node('C');
	MyBTree<char>::Node* D = new MyBTree<char>::Node('D');
	MyBTree<char>::Node* E = new MyBTree<char>::Node('E');
	MyBTree<char>::Node* F = new MyBTree<char>::Node('F');
	MyBTree<char>::Node* G = new MyBTree<char>::Node('G');

	A->left = B;

	B->left = C;
	B->right = D;

	A->right = E;

	E->left = F;
	E->right = G;

	cout << endl << "--PreOrder--" << endl;
	tree.PreOrder(A);
	cout << endl << "--InOrder--" << endl;
	tree.InOrder(A);
	cout << endl << "--PostOrder--" << endl;
	tree.PostOrder(A);
}

void TreeProcess()
{
	MyTree<char> tree;

	MyTree<char>::Node* A = MyTree<char>::CreateNode('A');
	MyTree<char>::Node* B = MyTree<char>::CreateNode('B');
	MyTree<char>::Node* C = MyTree<char>::CreateNode('C');
	MyTree<char>::Node* D = MyTree<char>::CreateNode('D');
	MyTree<char>::Node* E = MyTree<char>::CreateNode('E');
	MyTree<char>::Node* F = MyTree<char>::CreateNode('F');
	MyTree<char>::Node* G = MyTree<char>::CreateNode('G');
	MyTree<char>::Node* H = MyTree<char>::CreateNode('H');
	MyTree<char>::Node* I = MyTree<char>::CreateNode('I');
	MyTree<char>::Node* J = MyTree<char>::CreateNode('J');
	MyTree<char>::Node* K = MyTree<char>::CreateNode('K');

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

	MyTree<char>::DestroyNode(&A);
	MyTree<char>::DestroyNode(&B);
	MyTree<char>::DestroyNode(&C);
	MyTree<char>::DestroyNode(&D);
	MyTree<char>::DestroyNode(&E);
	MyTree<char>::DestroyNode(&F);
	MyTree<char>::DestroyNode(&G);
	MyTree<char>::DestroyNode(&H);
	MyTree<char>::DestroyNode(&I);
	MyTree<char>::DestroyNode(&J);
	MyTree<char>::DestroyNode(&K);
}

int main()
{
	TreeProcess();
	// BTreeProcess();
	_CrtDumpMemoryLeaks();
	return 0;
}