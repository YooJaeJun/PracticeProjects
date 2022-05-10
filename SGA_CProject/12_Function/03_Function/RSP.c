#include <stdio.h>
#include <Windows.h>
// 묵찌빠 게임을 구현해주세요.

// 조건 : 3판 2선승제로 구현해주세요.
//		함수를 하나 이상 사용하여 만들어주세요.

void printInput(int computer, int player) 
{
	printf("상대: %s \n", computer == 1 ? "가위" : computer == 2 ? "바위" : "보");
	printf("나: %s \n", player == 1 ? "가위" : player == 2 ? "바위" : player == 3 ? "보" : "유효하지 않은 번호");
}

int randomDice(int computer)
{
	computer = rand() % 3 + 1;	// 1 ~ 3 사이의 랜덤한 값을 뽑습니다.
	return computer;
}

void mukjipa(int computer, int player, int atkRight)
{
	computer = randomDice(computer);

	printf("번호를 입력하세요([1. 가위], [2. 바위], [3. 보]): ");
	scanf_s("%i", &player);
	printf("\n");

	printf("묵! 찌! 빠! \n");

	printInput(computer, player);

	if (computer == player)
	{
		printf("걸렸습니다! \n");
		printf("공격권을 가진 %s의 승리 ! \n", atkRight == 1 ? "player" : "computer");
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("이겼습니다 ! 공격권은 player ! \n");
		atkRight = 1;
		mukjipa(computer, player, atkRight);
	}
	else
	{
		printf("졌습니다 ! 공격권은 computer ! \n");
		atkRight = 2;
		mukjipa(computer, player, atkRight);
	}

}

int rockScissorsPaper(int computer, int player)
{
	computer = randomDice(computer);

	printf("번호를 입력하세요([1. 가위], [2. 바위], [3. 보]): ");
	scanf_s("%i", &player);
	printf("\n");

	printInput(computer, player);

	printf("\n");

	if (computer == player)
	{
		printf("무승부 ! 다시 시도해주세요. \n");
		rockScissorsPaper(computer, player);
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("이겼습니다 ! 공격권은 player ! \n");
		return 1;
	}
	else
	{
		printf("졌습니다 ! 공격권은 computer ! \n");
		return 2;
	}

	printf("\n");
}

int main()
{
	srand(GetTickCount64());
	int computer = 0;
	int player = 0;

	printf("묵찌빠 게임을 시작합니다. \n");


	printf("먼저 가위바위보를 해주세요. \n");
	int atkRight = rockScissorsPaper(computer, player);

	printf("\n");
	printf("묵찌빠를 시작합니다. \n");
	mukjipa(computer, player, atkRight);
	

	return 0;
}