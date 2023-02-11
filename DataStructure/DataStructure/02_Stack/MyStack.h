#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <cassert>

/// <summary>
/// LinkedList
/// </summary>
template<typename T>
struct Node
{
	T value;
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;

	Node() = default;
	Node(const T& other)
		: value(other), prev(nullptr), next(nullptr)
	{}
	Node(const Node<T>* other)
		: value(other->value), prev(other->prev), next(other->next)
	{}
	~Node()
	{}
};

template<typename T>
class MyStackByLinkedList
{
public:
	static Node<T>* Create(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		return newNode;
	}
	
	static void Destroy(Node<T>** data)
	{
		delete *data;
		*data = nullptr;
	}

public:
	MyStackByLinkedList() = default;
	MyStackByLinkedList(const T& data)
	{
		top->value = data;
	}

	~MyStackByLinkedList()
	{
		while (top)
		{
			Node<T>* temp = top->prev;
			Destroy(&top);
			top = temp;
		}
	}

public:
	Node<T>* Top() const
	{
		assert(top);
		return top;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}
	
	int Size() const
	{
		return size;
	}

	void Push(Node<T>* newNode)
	{
		Node<T>* temp = newNode;

		if (top)
		{
			temp->prev = top;
			top->next = temp;
		}

		top = temp;
		top->prev = temp->prev;

		size++;
	}

	Node<T>* Pop()
	{
		Node<T>* temp = top->prev;
		Node<T>* ret = new Node<T>(top);
		
		delete top;
		top = nullptr;

		if (temp)
		{
			temp->next = nullptr;
			top = temp;
			top->prev = nullptr;
			top->next = nullptr;
		}
		size--;

		return ret;
	}

private:
	Node<T>* top = nullptr;
	int size = 0;
};



/// <summary>
/// Array
/// </summary>
template<typename T>
class MyStackByArray
{
private:
	enum { MAX = 20 };

public:
	static MyStackByArray Create(const T& value)
	{
		MyStackByArray<T> st(value);
		return st;
	}
	static void Destroy(const MyStackByArray<T>** st)
	{
		delete *st;
		*st = nullptr;
	}

private:
	MyStackByArray() = default;
	MyStackByArray(const T& value)
	{
		data[0] = value;
		size = 1;
	}
	
public:
	~MyStackByArray()
	{
	}

	T Top() const
	{ 
		assert(size > 0);
		return data[size - 1]; 
	}
	
	bool IsEmpty() const
	{ 
		return size == 0;
	}
	
	void Push(T value)
	{
		assert(size <= MAX);
		data[size] = value;
		size++;
	}
	
	T Pop()
	{
		assert(size > 0);
		T ret = data[size - 1];
		size--;
		return ret;
	}
	
	int Size() const
	{
		return size;
	}

	void Print() const
	{
		for (const T& elem : data)
			std::cout << elem << ' ';
		std::cout << '\n';
	}

	
private:
	T data[MAX];
	int size = 0;
};

