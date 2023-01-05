#include <stdio.h>
// #include <iostream>
// using namespace std;

typedef struct tag
{
	int member;
	// char c;
} tag;

void a(static int b)
{
	// cout << b;
}

double Function(int a, int b)
{
	return 3.14;
}

int main()
{
	// int A = 10, B = 20;
	// cout << !(((A + 10) == 10) || (B != 20)) && A;
	// tag t;
	// cout << sizeof(t);

	// int Num[3];
	// Num = { 1, 2, 3 };

	// int Num = 10;
	// int* p = &Num;
	// int* p2 = p;
	// cout << p << '\n';
	// cout << p2 << '\n';
	// cout << & Num<< '\n';
	// cout << &* p2<< '\n';
	// cout << *&* p<< '\n';


	// int Array[5];
	// cout << Array << '\n';
	// cout << Array + 4 << '\n';

	// float Array[5] = { 1,2,3,4,5 };
	// cout << &(Array[3])	   << '\n';
	// cout <<    Array + 3   << '\n';
	// cout <<  112		   << '\n';
	// cout << &* (Array + 3) << '\n';
	// cout << &(*Array + 3) << '\n';

	// static int b = 5;
	// a(b);

	// double (*Func)(int, int) = Function;

	tag* p = (tag*)malloc(sizeof(tag) * 5);
	printf("%d \n", p->member	 );
	printf("%d \n", (*p).member);

	// p.member;
	// p[0]->member;
	// (*p)->member;
	// *(p + 1).member;
	// *(p[1])->member;


	tag monster;
	tag* pMonster = &monster;
	tag** ppMonster = &pMonster;

	monster.member;
	pMonster->member;
	(*pMonster).member;
	(ppMonster)->member;
	(*ppMonster)->member;


	// int a = 10;
	// int* ptr = &a;
	// ptr = 0			;
	// cout << ptr;
	// ptr = '\0'		;
	// cout << ptr;
	// ptr = '0'		;
	// cout << ptr;
	// ptr = NULL		;
	// cout << ptr;
	// ptr = ('A' - 65);
	// cout << ptr;
}