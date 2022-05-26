#include <stdio.h>

// DataType (자료형)
// 특정 공간을 어떻게 사용할지 결정하는 형식입니다.

// 자료형		Byte		범위
// char			1Byte			-128 ~ 127
// short		2Byte			-32,768 ~ 32,767
// int			4Byte		약	-21억 ~ 21억			// int 컴퓨터가 인식하는 가장 빠른 자료형
// long			4Byte		약	-21억 ~ 21억
// long long	8Byte		약	-92경 ~ 92경

int main()
{
	char MyChar = 127;
	printf("MyChar = %d \n", MyChar);
	// %d : 10진수 정수 형태의 데이터를 받아 출력해주는 형식 문자입니다.

	short myShort = -32768;
	printf("MyShort = %d \n", myShort);

	int myInt = 2100000000;
	printf("MyShort = %d \n", myInt);

	long myLong = -2100000000;
	printf("MyShort = %d \n", myLong);

	long long myLongLong = 9200000000000000;
	printf("MyShort = %lld \n", myLongLong);
	// %lld : %d로 출력하지 못하는 큰 정수형 데이터를 받아 출력해주는 형식 문자입니다.

	// unsigned : 음수를 나타낼 수 범위를 없애고 양수 범위로 늘려주는 키워드입니다.
	// Keyword : 언어에서 미리 제공된 단어를 의미합니다.
	// 사용 방법 : 자료형 앞에 작성하시면 됩니다.
	unsigned char myUnsigned = 255;
	printf("myUnsigned = %d \n", myUnsigned);

	// 2의 보수법
	// 모든 자리를 반전 시킵니다. (1은 0으로, 0은 1로)
	// 1을 더합니다.
	// (추후 비트 연산 수업에서 다시 강의)

	// char 는 문자를 저장할 수 있습니다.
	// 128 가지의 문자를 사용하실 수 있습니다.
	char A = 'A';
	int intA = 'A';

	printf("A : %c \n", A);
	printf("intA : %c \n", intA);
	// %c : 문자데이터를 받아 출력해주는 기능을 가지고 있습니다.

	// 실수 자료형
	// 자료형		Byte
	// float		4
	// double		8
	float myFloat = 3.14f;	// float형 변수에 값을 저장할 때는 끝에 f를 붙여주는 것이 좋습니다.
	double myDouble = 1.23456789;

	printf("myFloat : %f \n", myFloat);
	// %f : float 형태의 실수 데이터를 받아 출력하는 형식문자
	printf("myDouble : %lf \n", myDouble);
	// %lf : double 형태의 실수 데이터를 받아 출력하는 형식문자


	// %f, %lf 같은 경우 소수점 6자리까지 기본적으로 출력합니다.
	
	// 원하는 소수점 자리까지 표현하기 위해, 소수점 자리를 추가해야 합니다.
	printf("myFloat : %.2f \n", myFloat);
	printf("myDouble : %.8lf \n", myDouble);


	// printf("myFloat : %d \n", myFloat);

	// 변수의 이름 주의사항
	// 키워드를 사용해서는 안됩니다.
	// 중간에 공백을 넣어서는 안됩니다.
	// 특수기호는 _ 를 제외한 모든 기호가 불가능합니다.
	// 한글을 사용해서는 안됩니다.
	
	// int int;
	// int m y;
	int ★ = 7;
	int 재준 = 10;
	// visual studio 2017 버전부터 가능

	return 0;
}