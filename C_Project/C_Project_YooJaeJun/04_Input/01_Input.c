#include <stdio.h>

int main()
{
	// 입력받은 값을 저장할 변수를 선언합니다.
	int Num;

	// & : 주소 연산자
	//		해당 이름을 가지고 있는 공간의 주소(위치)를 가져옵니다.
	scanf_s("%i", &Num);
	printf("Num : %i \n", Num);
	printf("Num Address : %p \n", &Num);
	// %p : 주소값 형식의 데이터를 받아 출력해주는 서식문자입니다.

	// x64 8Byte
	// x86 4Byte
	
	// float 형 변수를 만들고 값을 입력받아 해당 변수의 값을 출력해주세요.
	float myFloat;
	printf("실수 형태의 데이터를 입력해주세요 : ");
	scanf_s("%f", &myFloat);
	printf("myFloat : %.2f \n", myFloat);


	return 0;
}