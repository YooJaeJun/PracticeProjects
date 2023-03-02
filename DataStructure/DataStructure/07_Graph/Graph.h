#pragma once

#include <iostream>

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

		while(node != nullptr)
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
	};

private:
	Node* head = nullptr;
	int count = 0;
};

