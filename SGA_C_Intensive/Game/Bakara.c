// 바카라 게임
// 1 ~ 13 사이의 숫자를 두 개를 뽑아
// 왼쪽이 큰지, 오른쪽이 큰지 아니면 같은지를 맞추는 게임입니다.

// 1. 컴퓨터는 1 ~ 13 의 두 개의 랜덤값을 뽑습니다.
// 2. 만약 Left : 1, Right : 3 을 뽑았을 때
// 3. Left, Middle, Right 를 선택합니다.
//    만약 뽑은 숫자가 Left 크거나, Right 크다면 1점을 얻습니다.
//    Middle(같다) 이라면 4점을 얻습니다.
//    만약 Left, Right 를 틀렸다면 1점을 잃습니다.
//    Middle(같다) 이라면 4점을 잃습니다.

// 총 10번 진행하며 마지막에 점수가 더 높은 사람이 이기는 게임입니다.

#include <stdio.h>
#include <Windows.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void shuffle(int card[], int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % i;
		swap(&card[i], &card[j]);
	}
}

// test
void printCard(int card[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%i ", card[i]);
	}
}

void title()
{
	printf("-----------------------------------------------------------\n");
	printf("[바카라 게임] 을 시작합니다. \n");
	printf("-----------------------------------------------------------\n");
}

int main()
{
	srand(GetTickCount64());

	title();

	const int n = 13;
	int card[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	Sleep(500);
	// printCard(card, n);

	int player = 0, dealer = 0;
	int t = 0;
	while (++t <= 10)
	{
		printf("-----------------------------------------------------------\n");
		printf("현재 플레이어 점수: %i \n", player);
		printf("현재 딜러 점수:     %i \n", dealer);
		printf("-----------------------------------------------------------\n");

		printf("딜러가 카드를 셔플합니다. \n");
		shuffle(card, n);
		printf("딜러가 카드 1 ~ 13 사이 카드를 두 장 뽑습니다. \n");
		int idx = 0;
		int left = card[idx++];
		int right = card[idx++];
		printf("두 장 중 한 장을 공개합니다. \n");
		printf("[ Left: %i, Right: ?? ] \n", left);

		printf("-----------------------------------------------------------\n");
		printf("두 수 중 어떤 수가 큰지 맞춰주세요. \n(Left가 클 것: 1. \nRight가 클 것: 2. \n둘이 같을 것(Middle): 3.) \n\n");
		int input;
		scanf_s("%d", &input);

		int playerPlusScore = 0;
		int dealerPlusScore = 0;
		if (input == 1)
		{
			if (left > right)
			{
				printf("정답 ! 1점을 획득합니다. \n");
				playerPlusScore = 1;
				dealerPlusScore = -1;
			}
			else if (left == right)
			{
				printf("실패 ! Left : %i, Right : %i 였습니다. \n", left, right);
				printf("Middle을 틀렸으므로 점수 -4점 ! \n");
				playerPlusScore = -4;
				dealerPlusScore = 4;
			}
			else
			{
				printf("실패 ! Left : %i, Right : %i 였습니다. \n", left, right);
				printf("점수 -1점 ! \n");
				playerPlusScore = -1;
				dealerPlusScore = 1;
			}
		}
		else if (input == 2)
		{
			if (left < right)
			{
				printf("정답 ! 1점을 획득합니다. \n");
				playerPlusScore = 1;
				dealerPlusScore = -1;
			}
			else if (left == right)
			{
				printf("실패 ! Left : %i, Right : %i 였습니다. \n", left, right);
				printf("Middle을 틀렸으므로 점수 -4점 ! \n");
				playerPlusScore = -4;
				dealerPlusScore = 4;
			}
			else
			{
				printf("실패 ! Left : %i, Right : %i 였습니다. \n", left, right);
				printf("점수 -1점 ! \n");
				playerPlusScore = -1;
				dealerPlusScore = 1;
			}
		}
		else if (input == 3)
		{
			if (left == right)
			{
				printf("정답 ! Middle 을 맞췄으므로 4점을 획득합니다. \n");
				playerPlusScore = 4;
				dealerPlusScore = -4;
			}
			else
			{
				printf("실패 ! Left : %i, Right : %i 였습니다. \n", left, right);
				printf("Middle을 틀렸으므로 점수 -4점 ! \n");
				playerPlusScore = -4;
				dealerPlusScore = 4;
			}
		}
		else
		{
			printf("잘못 입력했습니다. \n");

			if (left == right)
			{
				printf("Middle을 틀렸으므로 점수 -4점 ! \n");
				playerPlusScore = -4;
			}
			else
			{
				printf("실패 ! Left : %i, Right : %i 였습니다. \n", left, right);
				printf("점수 -1점 ! \n");
				playerPlusScore = -1;
			}
		}

		player += playerPlusScore;
		dealer += dealerPlusScore;

		printf("잠시 후 다시 셔플을 시작합니다. \n");
		Sleep(1500);
		system("cls");
	}

	printf("최종 플레이어 점수: %i \n", player);
	printf("최종 딜러 점수:     %i \n", dealer);
	printf("-----------------------------------------------------------\n");
	
	printf("최종 승리자는 %s !!! \n", player > dealer ? "플레이어" : player < dealer ? "딜러" : "없습니다! 무승부");

	printf("[바카라 게임] 을 종료합니다. \n");

	return 0;
}