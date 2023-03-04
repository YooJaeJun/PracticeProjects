#pragma once

#include <iostream>
#include <list>
#include "PQueue.h"

template<typename T>
class Graph
{
public:
	struct Edge;
	struct Node;

public:
	void AddNode(Node* node)
	{
		Node* nodeList = head;
		if (nodeList != nullptr)
		{
			while (nodeList->next != nullptr)
				nodeList = nodeList->next;

			nodeList->next = node;
		}
		else
			head = node;

		node->index = count++;
	}

	void AddEdge(Node* node, Edge* edge)
	{
		if (node->edge != nullptr)
		{
			Edge* edgeList = node->edge;

			while (edgeList->next != nullptr)
				edgeList = edgeList->next;

			edgeList->next = edge;
		}
		else
			node->edge = edge;
	}

	void Print()
	{
		Node* node = nullptr;
		Edge* edge = nullptr;

		if ((node = head) == nullptr)
			return;

		while (node != nullptr)
		{
			std::cout << node->data << " : ";

			if ((edge = node->edge) == nullptr)
			{
				node = node->next;
				std::cout << '\n';

				continue;
			}

			while (edge != nullptr)
			{
				std::cout << edge->target->data;
				edge = edge->next;
			}

			std::cout << '\n';

			node = node->next;
		}

		std::cout << '\n';
	}

	void InitVisited(Node* n)
	{
		while (n)
		{
			n->visited = false;
			n = n->next;
		}
	}

	void Prim(Node* startNode, Graph<T>* graph)
	{
		Node* currentNode = NULL;
		Edge* currentEdge = NULL;

		int* weights = new int[count];
		Node** mstNodes = new Node * [count];
		Node** friends = new Node * [count];
		Node** parents = new Node * [count];

		// �ʱ�ȭ
		int index = 0;
		currentNode = head;
		while (currentNode != NULL)
		{
			Graph<T>::Node* newNode = CreateNode(currentNode->data);
			graph->AddNode(newNode);

			friends[index] = NULL;
			parents[index] = NULL;
			weights[index] = INT_MAX;
			currentNode = currentNode->next;

			index++;
		}

		// ���� ����
		PQueue<Node*> queue;
		PQueue<Node*>::Node startQueueNode = PQueue<Node*>::Node(0, startNode);

		queue.Insert(startQueueNode);
		weights[startNode->index] = 0;		// index�� A�� 0, B�� 1, ...

		// BFS�� �����ϰ� �켱���� ť�� �ĺ��� �� �־����
		while (queue.Empty() == false)
		{
			PQueue<Node*>::Node poped = queue.RemoveMin();

			currentNode = poped.data;
			friends[currentNode->index] = currentNode;

			currentEdge = currentNode->edge;
			while (currentEdge != NULL)
			{
				Node* targetNode = currentEdge->target;		// Ÿ�� == ÷�� ���(B) �Ʒ��� A ���� ����

				if (friends[targetNode->index] == NULL &&	/* ������尡 �ƴ� */
					currentEdge->weight < weights[targetNode->index])	/* Ÿ�ٿ� �ִ� ����ġ�� �ڱ⺸�� ������ */
				{
					PQueue<Node*>::Node newNode = PQueue<Node*>::Node(currentEdge->weight, targetNode);
					queue.Insert(newNode);

					parents[targetNode->index] = currentEdge->start;
					weights[targetNode->index] = currentEdge->weight;
				}

				currentEdge = currentEdge->next;
			}//while(currentEdge)
		}//while(queue)
	}

public:
	static Edge* CreateEdge(Node* start, Node* target)
	{
		Edge* edge = new Edge();
		edge->start = start;
		edge->target = target;
		edge->next = nullptr;

		return edge;
	}

	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->data = data;

		return node;
	}

public:
	struct Edge
	{
		int weight = 0;
		Node* start = nullptr;
		Node* target = nullptr;
		Edge* next = nullptr;
	};

	struct Node
	{
		T data;
		int index = -1;

		Node* next = nullptr;
		Edge* edge = nullptr;

		bool visited = false;
	};

private:
	Node* head = nullptr;
	int count = 0;
};

