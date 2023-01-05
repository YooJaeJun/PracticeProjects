#include <iostream>

// 선택적 매개변수 (Optional Prameter)
// Cpp 에서부터는 매개변수에 기본값을 줄 수 있는 선택적 매개변수를 제공합니다.
// 선택적 매개변수는 필요에 따라 함수 호출 시 생략이 가능하며
// 생략할 시에 설정한 기본값이 들어갑니다.
// 반드시 필수 매개변수 (함수 호출 시 반드시 작성해야하는) 매개변수 뒤에 작성하셔야 합니다.
// 선택적 매개변수는 한 개가 아닌 여러 개도 사용 가능합니다.

//							sizePrint 에 false 라는 기본값을 작성해 선택적 매개변수로 만듭니다.
void checkInt(int integer = 1, bool sizePrint = false)
{
	if (sizePrint)
		std::cout << "integer Size : " << sizeof(integer) << '\n';
	
	std::cout << "inter Value  : " << integer << '\n';
}

// void Print(int num1, int num2 = 0, int num3)	// 다음과 같은 선언은 불가능
void Print(int num1, int num2 = 0, int num3 = 0)
{
	printf("num1 : %i \n", num1);
	if (num2)
		printf("num2 : %i \n", num2);
	if (num3)
		printf("num3 : %i \n", num3);
}

// 선택적 매개변수로만 매개변수 목록을 채울 수도 있습니다.
void optionalParameter(bool boolean = false)
{
	printf("boolean : %s \n", (boolean ? "True" : "False"));
}

int main()
{
	checkInt(10, true);
	checkInt(20, false);
	checkInt(20);
	checkInt();

	Print(10);
	Print(10, 20);
	Print(10, 20, 30);

	optionalParameter(true);
	optionalParameter();


	return 0;
}
