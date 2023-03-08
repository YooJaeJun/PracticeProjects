#pragma once

#include <iostream>
#include <list>
#include "PQueue.h"
#include "DisjointSet.h"

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
		Node** connected = new Node * [count];
		Node** parents = new Node * [count];

		// 초기화
		int index = 0;
		currentNode = head;
		while (currentNode != NULL)
		{
			Graph<T>::Node* newNode = CreateNode(currentNode->data);
			graph->AddNode(newNode);

			weights[index] = INT_MAX;
			mstNodes[index] = newNode;
			connected[index] = NULL;
			parents[index] = NULL;
			currentNode = currentNode->next;

			index++;
		}

		// 본격 시작
		PQueue<Node*> queue(10);
		PQueue<Node*>::Node startQueueNode = PQueue<Node*>::Node(0, startNode);

		queue.Insert(startQueueNode);
		weights[startNode->index] = 0;		// index는 A면 0, B면 1, ...

		// BFS와 유사하게 우선순위 큐에 후보들 다 넣어놓기
		while (queue.Empty() == false)
		{
			PQueue<Node*>::Node poped = queue.RemoveMin();

			currentNode = poped.data;
			connected[currentNode->index] = currentNode;

			// std::cout << currentNode->data;

			currentEdge = currentNode->edge;
			while (currentEdge != NULL)
			{
				Node* targetNode = currentEdge->target;		// 타겟 == 첨엔 헤드(B) 아래에 A 노드로 생각

				if (connected[targetNode->index] == NULL &&	/* 리프노드가 아님 */
					currentEdge->weight < weights[targetNode->index])	/* 타겟에 있는 가중치가 자기보다 작은지 */
				{
					PQueue<Node*>::Node newNode = PQueue<Node*>::Node(currentEdge->weight, targetNode);
					queue.Insert(newNode);

					parents[targetNode->index] = currentEdge->start;
					weights[targetNode->index] = currentEdge->weight;
				}

				currentEdge = currentEdge->next;
			}//while(currentEdge)
		}//while(queue)

		//std::cout << '\n';

		//for (int i = 0; i < count; i++)
		//{
		//	std::cout << i << "," << weights[i] << " / ";
		//}

		for (int i=0; i<count; i++)
		{
			int start, target;

			if (parents[i] == NULL)
				continue;

			start = parents[i]->index;
			target = i;

			graph->AddEdge(mstNodes[start], Graph<T>::CreateEdge(mstNodes[start], mstNodes[target], weights[i]));
			graph->AddEdge(mstNodes[target], Graph<T>::CreateEdge(mstNodes[target], mstNodes[start], weights[i]));

			std::cout << mstNodes[start]->data << " -> " << mstNodes[target]->data << ", " << weights[i] << '\n';
		}

		cout << '\n';

		delete[] weights;
		delete[] mstNodes;
		delete[] connected;
		delete[] parents;
	}

	void Kruskal(Graph<T>* graph)
	{
		Node** mstNodes = new Node * [count];
		PQueue<Edge*> queue(10);

		DisjointSet<Node*>::Set** sets = new DisjointSet<Node*>::Set*[count];

		int index = 0;
		Node* currentNode = head;
		Edge* currentEdge = NULL;
		while (currentNode != NULL)
		{
			sets[index] = DisjointSet<Node*>::CreateSet(currentNode);
			mstNodes[index] = CreateNode(currentNode->data);
			graph->AddNode(mstNodes[index]);

			currentEdge = currentNode->edge;
			while (currentEdge != NULL)
			{
				PQueue<Edge*>::Node newNode = PQueue<Edge*>::Node(currentEdge->weight, currentEdge);
				queue.Insert(newNode);

				currentEdge = currentEdge->next;
			}

			currentNode = currentNode->next;
			index++;
		}

		while (queue.Empty() == false)
		{
			PQueue<Edge*>::Node poped = queue.RemoveMin();
			currentEdge = poped.data;
			
			int start = currentEdge->start->index;
			int target = currentEdge->target->index;


			// 핵심
			if (DisjointSet<Node*>::FindSet(sets[start]) == DisjointSet<Node*>::FindSet(sets[target]))
				continue;

			DisjointSet<Node*>::UnionSet(sets[start], sets[target]);

			graph->AddEdge(mstNodes[start], Graph<T>::CreateEdge(mstNodes[start], mstNodes[target], currentEdge->weight));
			graph->AddEdge(mstNodes[target], Graph<T>::CreateEdge(mstNodes[target], mstNodes[start], currentEdge->weight));

			std::cout << mstNodes[start]->data << " -> " << mstNodes[target]->data << ", " << currentEdge->weight << '\n';
		}
	}

public:
	static Edge* CreateEdge(Node* start, Node* target, int weight)
	{
		Edge* edge = new Edge();
		edge->start = start;
		edge->target = target;
		edge->next = nullptr;
		edge->weight = weight;

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

