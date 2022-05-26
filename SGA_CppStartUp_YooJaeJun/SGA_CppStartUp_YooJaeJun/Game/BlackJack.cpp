#include <stdio.h>
#include <string.h>
#include <Windows.h>
#pragma warning(disable : 4996)

typedef struct tag_Player
{
	char cards[10][5];
	int cardCount;
	int sum;
} Player;

void printDeck(char deck[4][13][5])
{
	printf("\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			printf("%s ", deck[i][j]);
		}
		printf("\n");
	}
}

void createDeck(char deck[4][13][5])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			switch (i)
			{
			case 0: strcpy(deck[i][j], "♤");
				break;
			case 1: strcpy(deck[i][j], "♡");
				break;
			case 2: strcpy(deck[i][j], "♧");
				break;
			case 3: strcpy(deck[i][j], "◇");
				break;
			}

			int num = j + 1;

			switch (num)
			{
			case 1:
			{
				strcat(deck[i][j], "A");
				break;
			}
			case 11:
			{
				strcat(deck[i][j], "J");
				break;
			}
			case 12:
			{
				strcat(deck[i][j], "Q");
				break;
			}
			case 13:
			{
				strcat(deck[i][j], "K");
				break;
			}
			default:
			{
				char str[3];
				// strcat(str1, str2) : str1 에 str2 의 문자열을 잇습니다.
				// itoa(value, str, expression) : 정수 형식을 문자열로 바꿉니다.
				// - value      : 문자열로 바꿀 정수
				// - str		: 바꾼 문자열을 저장할 배열
				// - expression : 표현할 진수
				strcat(deck[i][j], itoa(num, str, 10));
				break;
			}
			}
		}
	}
}

void shuffle(char deck[4][13][5])
{
	srand(GetTickCount64());

	for (int i = 0; i < 52; i++)
	{
		int randomIndex_1 = rand() % 4;
		int randomIndex_2 = rand() % 13;
		int randomIndex_3 = rand() % 4;
		int randomIndex_4 = rand() % 13;

		char temp[5] = { 0 };
		strcpy(temp, deck[randomIndex_1][randomIndex_2]);
		strcpy(deck[randomIndex_1][randomIndex_2], deck[randomIndex_3][randomIndex_4]);
		strcpy(deck[randomIndex_3][randomIndex_4], temp);
	}
}

char* draw(char deck[4][13][5], Player* player)
{
	// 정적변수
	static int OneIndex = 0;
	static int TwoIndex = 0;
	
	strcpy(player->cards[player->cardCount], deck[OneIndex][TwoIndex]);
	// -> : 멤버 간접 접근 연산자
	// (*StructAddress).Member
	// StructAddress->member
	//		. (멤버 직접접근 연산자) 와 다르게 구조체의 주소값에 접근하여
	//		멤버간접접근 하는 연산자입니다.

	if (++TwoIndex == 13)
	{
		OneIndex++;
		TwoIndex = 0;
		printf("\n");
	}

	++player->cardCount;
}

int calculate(Player* player)
{
	for (int i = 0; i < player->cardCount; i++)
	{
		char str[3];
		// strlen : 널문자를 제외한 문자열의 길이를 반환합니다.
		// strncpy(player->cards[i], ,strlen(player->cards[i]));
	}
}

int main()
{
	printf("♤ size : %i", sizeof(char));
	printf("♡ size : %i", sizeof(char));
	printf("♧ size : %i", sizeof(char));
	printf("◇ size : %i", sizeof(char));
	
	
	char deck[4][13][5];	// 행, 열, 문자열
	createDeck(deck);
	printDeck(deck);
	shuffle(deck);
	//system("pause");
	system("cls");
	printDeck(deck);

	Player player;

	// main 문에서 구조체 멤버 초기화

	// deck 에서 카드를 뽑아 player의 Cards에 저장하는 함수를 만들어주세요.
	printf("\nplayer card draw : ");
	int t = 10;
	while (t--)
	{
		printf("%s \n", draw(deck, &player));


	}

	return 0;
}