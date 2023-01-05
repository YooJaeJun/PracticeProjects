#include <stdio.h>
#include <Windows.h>

// 가위바위보 게임을 만들어주세요.

int main()
{
	srand(GetTickCount64());
	int computer = rand() % 3 + 1;	// 1 ~ 3 사이의 랜덤한 값을 뽑습니다.
	// 1. 가위
	// 2. 바위
	// 3. 보

	printf("가위바위보 게임을 시작합니다. \n");
	printf("번호를 입력하세요([1. 가위], [2. 바위], [3. 보]): ");
	int mine;
	scanf_s("%i", &mine);

	printf("\n");

	printf("상대: %s \n", computer == 1 ? "가위" : computer == 2 ? "바위" : "보");
	printf("나: %s \n", mine == 1 ? "가위" : mine == 2 ? "바위" : mine == 3 ? "보" : "유효하지 않은 번호");

	printf("\n");

	if (computer == mine) 
	{
		printf("무승부 !");
	}
	else if ((computer == 1 && mine == 2) ||
		(computer == 2 && mine == 3) ||
		(computer == 3 && mine == 1)) 
	{
		printf("이겼습니다 !");
	}
	else 
	{
		printf("졌습니다 ㅜ_ㅜ");
	}

	printf("\n");

	return 0;
}