#include <stdio.h>

// switch case 문
// case 에 따라 실행할 코드를 분류합니다.
// case 는 반드시 상수여야 합니다.

// switch(A)
// {
// case A : 케이스가 A 일 때 실행할 구문
//	break;
// case B :	케이스가 B 일 때 실행할 구문
//	break;
// case C : case D :	케이스가 C 거나 D 일 때 실행할 구문
// default : 케이스가 A 와 B 가 모두 아닐 때 실행할 구문
//	break;
// }

int main()
{
	int input;
	printf("입력 : ");
	scanf_s("%i", &input);
	
	switch (input) {
	case 1:
		printf("입력한 값은 1입니다. \n");
		break;
	case 2:
		printf("입력한 값은 2입니다. \n");
		break;
	case 3:
		printf("입력한 값은 3입니다. \n");
		break;
	case 4:
		printf("입력한 값은 4입니다. \n");
	case 5:
		printf("입력한 값은 5입니다. \n");
		break;
	default :
		printf("입력한 값은 1, 2, 3, 4, 5 가 아닙니다. \n");
		break;
	}

	
	if (input < 0) printf("음수입니다. \n");
	else 
	{
		switch (input % 2)
		{
		case 0:
			if (input == 0) printf("0 입니다.");
			else printf("짝수입니다. \n");
			break;
		case 1:	printf("홀수입니다. \n");
			break;
		}
	}

	// 비교할 대상이 2개 이하라면 if 문의 속도가 빠릅니다.
	// 3개 이상이라면 switch~case 문의 속도가 더 빠릅니다.
	// 복잡한 형식의 비교 대상이라면 if 문을 
	// 간단한 형식이지만 많은 대상을 비교하고 싶다면 switch~case 문을 사용하는 것이 좋습니다.

	// 경우1 hp < 0 : if
	// 경우2 WASD 이동 : switch~case
}