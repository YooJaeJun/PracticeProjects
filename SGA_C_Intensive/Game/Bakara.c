// ��ī�� ����
// 1 ~ 13 ������ ���ڸ� �� ���� �̾�
// ������ ū��, �������� ū�� �ƴϸ� �������� ���ߴ� �����Դϴ�.

// 1. ��ǻ�ʹ� 1 ~ 13 �� �� ���� �������� �̽��ϴ�.
// 2. ���� Left : 1, Right : 3 �� �̾��� ��
// 3. Left, Middle, Right �� �����մϴ�.
//    ���� ���� ���ڰ� Left ũ�ų�, Right ũ�ٸ� 1���� ����ϴ�.
//    Middle(����) �̶�� 4���� ����ϴ�.
//    ���� Left, Right �� Ʋ�ȴٸ� 1���� �ҽ��ϴ�.
//    Middle(����) �̶�� 4���� �ҽ��ϴ�.

// �� 10�� �����ϸ� �������� ������ �� ���� ����� �̱�� �����Դϴ�.

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
	printf("[��ī�� ����] �� �����մϴ�. \n");
	printf("-----------------------------------------------------------\n");
}

void success(int* playerPlusScore, int* dealerPlusScore, int score)
{
	printf("���� ! %i���� ȹ���մϴ�. \n", score);
	if (score == 4) printf("Middle�� ���������Ƿ� ������ ũ�� �����ϴ�. \n");
	*playerPlusScore += score;
	*dealerPlusScore -= score;
}

void fail(const int left, const int right, int* playerPlusScore, int* dealerPlusScore, int score)
{
	printf("���� ! Left : %i, Right : %i �����ϴ�. \n", left, right);
	if (score == -4) printf("Middle�� ���������Ƿ� ������ ũ�� ���Դϴ�. \n");
	printf("���� %i�� ! \n", score);
	*playerPlusScore += score;
	*dealerPlusScore -= score;
}

int main()
{
	// ���� �ð��� ��ȯ
	// �и� ������
	srand(GetTickCount64());

	title();

	const int n = 13;
	int card[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	Sleep(500);
	// printCard(card, n);

	int player = 0, dealer = 0;
	int t = 0;
	int playerPlusScore = 0;
	int dealerPlusScore = 0;

	while (++t <= 10)
	{
		printf("-----------------------------------------------------------\n");
		printf("���� �÷��̾� ����: %i \n", playerPlusScore);
		printf("���� ���� ����:     %i \n", dealerPlusScore);
		printf("-----------------------------------------------------------\n");

		printf("������ ī�带 �����մϴ�. \n");
		shuffle(card, n);
		printf("������ ī�� 1 ~ 13 ���� ī�带 �� �� �̽��ϴ�. \n");
		int idx = 0;
		int left = card[idx++];
		int right = card[idx++];
		printf("�� �� �� �� ���� �����մϴ�. \n");
		printf("[ Left: %i, Right: ?? ] \n", left);

		printf("-----------------------------------------------------------\n");
		printf("�� �� �� � ���� ū�� �����ּ���. \n(Left�� Ŭ ��: 1. \nRight�� Ŭ ��: 2. \nMiddle ���� ���� ��: 3.) \n\n");
		int input;
		scanf_s("%d", &input);

		if (input == 1)
		{
			if (left > right)
			{
				success(&playerPlusScore, &dealerPlusScore, 1);
			}
			else if (left == right)
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -4);
			}
			else
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -1);
			}
		}
		else if (input == 2)
		{
			if (left < right)
			{
				success(&playerPlusScore, &dealerPlusScore, 1);
			}
			else if (left == right)
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -4);
			}
			else
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -1);
			}
		}
		else if (input == 3)
		{
			if (left == right)
			{
				success(&playerPlusScore, &dealerPlusScore, 4);
			}
			else
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -4);
			}
		}
		else
		{
			printf("�߸� �Է��߽��ϴ�. \n");

			if (left == right)
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -4);
			}
			else
			{
				fail(left, right, &playerPlusScore, &dealerPlusScore, -1);
			}
		}

		player += playerPlusScore;
		dealer += dealerPlusScore;

		printf("��� �� �ٽ� ������ �����մϴ�. \n");
		Sleep(1500);
		system("cls");
	}

	printf("���� �÷��̾� ����: %i \n", player);
	printf("���� ���� ����:     %i \n", dealer);
	printf("-----------------------------------------------------------\n");
	
	printf("���� �¸��ڴ� %s !!! \n", player > dealer ? "�÷��̾�" : player < dealer ? "����" : "�����ϴ�! ���º�");

	printf("[��ī�� ����] �� �����մϴ�. \n");

	return 0;
}