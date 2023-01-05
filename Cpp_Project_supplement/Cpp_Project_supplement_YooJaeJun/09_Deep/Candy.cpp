#include "Candy.h"

S_Candy::S_Candy()
{
	Name = "Lime";
	Price = 250;
}

S_Candy::S_Candy(const S_Candy& Copy)
{
	Name = Copy.Name;
	Price = Copy.Price;
}

void S_Candy::SetPrice(int newPrice)
{
	Price = newPrice;
}

void S_Candy::Print()
{
	cout << "Name  : " << Name << endl;
	cout << "Price : " << Price << endl;
}

D_Candy::D_Candy()
{
	Name = "De";
	Price = new int;	// int 형 값을 저장하기 위해 동적할당
	*Price = 250;
}

D_Candy::D_Candy(const D_Candy& Copy)
{
	Name = Copy.Name;
	Price = new int(*Copy.Price);	// 깊은 복사
	// Price = Copy.Price;	// 얕은 복사
}

void D_Candy::SetPrice(int newPrice)
{
	*Price = newPrice;
}

void D_Candy::Print()
{
	cout << "Name : " << Name << endl;
	cout << "Price: " << *Price << endl;
}
