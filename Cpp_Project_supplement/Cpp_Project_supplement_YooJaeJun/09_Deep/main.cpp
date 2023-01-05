#include "Candy.h"

int main()
{
	S_Candy s_candy_1;
	S_Candy s_candy_2 = s_candy_1;
	s_candy_2.SetPrice(300);
	s_candy_1.Print();
	s_candy_2.Print();

	printf("\n");

	D_Candy d_candy_1;
	D_Candy d_candy_2 = d_candy_1;
	d_candy_2.SetPrice(300);
	d_candy_1.Print();	// d_candy_1 priceµµ º¯°æµÊ
	d_candy_2.Print();


	return 0;
}