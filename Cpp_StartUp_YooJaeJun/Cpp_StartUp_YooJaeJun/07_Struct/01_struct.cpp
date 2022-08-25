#include <iostream>

// C
/*
typedef struct tag_myStruct
{
	int a;
	int b;
	int c;

}myStruct;
*/

// Cpp
// typedef 을 사용하지 않고 구조체 변수의 선언이 가능합니다.
struct myStruct
{
	// 멤버 변수에 기본값을 넣어줄 수 있습니다.
	int a = 10;
	int b = 20;
	int c = 30;

	// 멤버 함수가 추가됩니다.
	// 객체 : 설계도를 바탕으로 만들어진 오브젝트
	void print()	// 호출하는 객체를 기준으로 멤버에 접근합니다.
	{
		printf("a : %i \n", a);
		printf("b : %i \n", b);
		printf("c : %i \n", c);
	}
};

int main()
{
	myStruct myStruct_1;
	printf("myStruct_1.a : %i \n", myStruct_1.a);
	printf("myStruct_1.b : %i \n", myStruct_1.b);
	printf("myStruct_1.c : %i \n", myStruct_1.c);
	std::cout << '\n';

	printf("myStruct_1 의 멤버 출력 \n");
	myStruct_1.print();
	std::cout << '\n';

	myStruct myStruct_2;
	myStruct_2.a = 100;
	printf("myStruct_2 의 멤버 출력 \n");
	myStruct_2.print();
	std::cout << '\n';

	/*
	
	C (절차 지향적 언어)
	- 함수 지향적 언어
	- 디자인이 단순함
	- 복잡한 코드를 작성하기 맞지 않음
	- 속도가 매우 빠른 것이 특징
	- 구조 설계에 시간이 적게 든다.
	
	CPP (객체 지향적 언어)
	- 객체
	- 디자인이 복잡함
	- 복잡한 코드를 작성하기 알맞음
	- 구조 설계가 매우 어려움
	- 속도가 느립니다.

	객체: 설계도를 바탕으로 만들어진 오브젝트
	- 설계도: class, struct
	- 오브젝트: 변수
	- 같은 설계도로 만들어진 객체들은 자기 자신만의 값을 갖고
	- 다른 객체가 변경되더라도 같이 변경되지 않는 것이 특징입니다.

	*/

	return 0;
}
