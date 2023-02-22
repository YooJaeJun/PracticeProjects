#include <iostream>
#include "_MyBinarySearchTree.h"
using namespace std;

typedef MyBinarySearchTree<int> Tree;

int main()
{
	Tree tree;
	Tree::Node* root = Tree::CreateNode(123);
	tree.SetRoot(root);

	tree.Insert(&root, Tree::CreateNode(22));
	tree.Insert(&root, Tree::CreateNode(99));
	tree.Insert(&root, Tree::CreateNode(42));
	tree.Insert(&root, Tree::CreateNode(17));
	tree.Insert(&root, Tree::CreateNode(3));
	tree.Insert(&root, Tree::CreateNode(98));
	tree.Insert(&root, Tree::CreateNode(34));
	tree.Insert(&root, Tree::CreateNode(75));
	tree.Insert(&root, Tree::CreateNode(32));
	tree.Insert(&root, Tree::CreateNode(1));

	tree.InOrder(root, 0);

	int depth = 0;
	Tree::Node* node = tree.Search(root, 98, depth);
	cout << endl << endl << "찾기 : " << node->data << " " << depth << "번에 찾음\n";

	node = tree.Remove(root, NULL, 98);
	cout << "삭제할 노드 : " << node->data << endl;
	Tree::DestroyNode(&node);

	tree.InOrder(root, 0);
	cout << endl << endl;

	return 0;
}