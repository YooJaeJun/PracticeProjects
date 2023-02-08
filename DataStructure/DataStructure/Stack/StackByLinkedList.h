#pragma once
#include <string>
using namespace std;

struct Node
{
	string Data;
	Node* NextNode;
};

class StackByLinkedList
{
public:
	StackByLinkedList();
	~StackByLinkedList();

	void Push(Node* node);
	Node* Pop();

	Node* Top() { return top; }
	int Size();
	bool IsEmpty() { return list == NULL; }

	static Node* CreateNode(string data);
	static void DestroyNode(Node** node);

private:
	Node* list = NULL;
	Node* top = NULL;
};

