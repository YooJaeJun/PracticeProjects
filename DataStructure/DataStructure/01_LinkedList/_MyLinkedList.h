#pragma once
#include <iostream>
#include <cassert>

template<typename T>
struct Node
{
	Node() : value(0), prev(nullptr), next(nullptr) {}
	Node(T value) : value(value), prev(nullptr), next(nullptr)
	{}
	Node(T value, Node* prev, Node* next)
		: value(value), prev(prev), next(next)
	{}
	~Node()
	{
		value = 0;
		prev = nullptr;
		next = nullptr;
	}
	T value;
	Node<T>* prev;
	Node<T>* next;
};

template<typename T>
class MyLinkedList
{
public:
	static MyLinkedList<T>* Create(T value)
	{
		MyLinkedList<T>* ret = new MyLinkedList<T>(value);
		return ret;
	}

private:
	MyLinkedList(T value)
	{
		head = new Node<T>(value);
		tail = head;
	}

public:
	~MyLinkedList()
	{
		Clear();
	}

	void PushBack(Node<T>* newNode)
	{
		if (tail)
			Insert(tail, newNode);
		else
		{
			head = newNode;
			tail = head;
		}
	}

	void PushBack(T value)
	{
		Node<T>* temp = new Node<T>(value);
		PushBack(temp);
	}

	void PushFront(Node<T>* newNode)
	{
		Insert(-1, newNode);
	}

	void PushFront(T value)
	{
		Node<T>* temp = new Node<T>(value);
		PushFront(temp);
	}
	
	void Insert(int index, Node<T>* newNode)
	{
		Node<T>* current = GetNode(index);
		Insert(current, newNode);
	}

	// 실질적인 삽입이 이루어지는 곳
	void Insert(Node<T>* current, Node<T>* newNode)
	{
		if (head == nullptr)
		{
			head = newNode;
		}
		else if (current == nullptr)
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		else
		{
			if (current == tail || tail == nullptr)
				tail = newNode;


			newNode->next = current->next;
			newNode->prev = current;

			if (current->next)
				current->next->prev = newNode;

			current->next = newNode;
		}
	}

	void Remove(const int index)
	{
		Node<T>* target = GetNode(index);
		Remove(target);
	}

	// 실질적인 삭제가 이루어지는 곳
	void Remove(Node<T>* target)
	{
		if (target == nullptr)
		{
			std::cout << "target이 nullptr인데 Remove 시도\n";
			assert(false);
		}

		if (target == head)
			head = target->next;

		if (target == tail)
			tail = target->prev;


		if (target->next)
			target->next->prev = target->prev;

		if (target->prev)
			target->prev->next = target->next;

		target->next = nullptr;
		target->prev = nullptr;
		delete target;
		target = nullptr;
	}

	void Clear()
	{
		Node<T>* temp = tail;
		while (temp)
		{
			temp = tail->prev;
			delete tail;
			tail = temp;
		}
		head = nullptr;
		tail = nullptr;
	}

	Node<T>* GetNode(const int index) const
	{
		if (index == -1)
			return nullptr;

		Node<T>* ret = head;
		int start = 0;

		while (ret && start != index)
		{
			ret = ret->next;
			start++;
		}

		if (ret == nullptr)
		{
			std::cout << "잘못된 Index 입력\n";
			assert(false);
		}

		return ret;
	}

	int GetSize() const
	{
		Node* temp = head;
		int size = 0;

		while (temp)
		{
			size++;
			temp = temp->next;
		}

		return size;
	}

	bool IsEmpty() const 
	{ 
		return head == nullptr; 
	}

	void Print()
	{
		Node<T>* temp = head;

		while (temp)
		{
			std::cout << temp->value << ' ';
			temp = temp->next;
		}

		std::cout << '\n';
	}

private:
	Node<T>* head;
	Node<T>* tail;
};

