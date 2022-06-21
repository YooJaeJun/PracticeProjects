#pragma once
#include <iostream>
using namespace std;

class S_Candy
{
private :
	string Name;
	int	   Price;

public:
	S_Candy();

	S_Candy(const S_Candy& Copy);

	void SetPrice(int newPrice);

	void Print();
};

class D_Candy
{
private:
	string Name;
	int*   Price;

public:
	D_Candy();

	D_Candy(const D_Candy& Copy);

	void SetPrice(int newPrice);

	void Print();
};

