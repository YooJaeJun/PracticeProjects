#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

struct Card
{
	string Shape  = "";
	string Number = "";
	int    Size   = 0;

	__forceinline void Print()
	{
		cout << Shape << Number;
	}
};

typedef struct Player
{
	// 정적 멤버 변수
	// 모든 객체들이 공유하는 멤버입니다.
	// 전역에서 초기화를 해주셔야 합니다.
	// 초기화 방법 : [정적멤버변수의 자료형] [설계도::변수] = value;
	static int Index;
	Card OwnCard[10];
	int OwnCount = 0;
	int Sum = 0;

	void Draw(Card* deck)
	{
		OwnCard[OwnCount] = deck[Index];
		++OwnCount;
		++Index;
	}

	int Calculate()
	{
		Sum = 0;
		int ACount = 0;
		for (int i = 0; i < OwnCount; i++)
		{
			Sum += OwnCard[i].Size;
			if (OwnCard[i].Size == 1) ++ACount;
		}

		if (ACount)
		{
			for (int i = 0; i < ACount; i++)
			{
				int temp = Sum;

				temp += 10;

				if (temp > 21) break;
				else Sum = temp;
			}
		}

		return Sum;
	}

	void Print()
	{
		cout << "소유 카드 : ";
		for (int i = 0; i < OwnCount; i++)
		{
			OwnCard[i].Print();
			cout << " ";
		}
		cout << endl;
		cout << "합계 : " << Calculate() << endl;
	}
}Dealer;

int Player::Index = 0;

Card* CreateDeck()
{
	Card* deck = new Card[52];

	int N = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			switch (i)
			{
			case 0: deck[N].Shape = "♤"; break;
			case 1: deck[N].Shape = "♡"; break;
			case 2: deck[N].Shape = "♧"; break;
			case 3: deck[N].Shape = "◇"; break;
			}

			int Num = j + 1;

			deck[N].Size = Num;
			if (deck[N].Size > 10) deck[N].Size = 10;

			switch (Num)
			{
			case 1:
				deck[N].Number = "A"; break;
			case 11:
				deck[N].Number = "J"; break;
			case 12:
				deck[N].Number = "Q"; break;
			case 13:
				deck[N].Number = "K"; break;
			default:
				deck[N].Number = to_string(Num);
				break;
			}// switch

			++N;
		}
	}

	return deck;
}

void PrintDeck(Card* deck)
{
	int N = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			deck[N].Print();
			++N;
		}
		printf("\n");
	}
}

void Shuffle(Card* deck)
{
	srand(GetTickCount64());
	for (int i = 0; i < 52; i++)
	{
		int r1 = rand() % 52;
		int r2 = rand() % 52;

		Card temp = deck[r1];
		deck[r1] = deck[r2];
		deck[r2] = temp;
	}
}

int main()
{
	Card* Deck = CreateDeck();
	Player* player = new Player();
	Dealer* dealer = new Dealer();

	Shuffle(Deck);

	int Input = 0;
	player->Draw(Deck);
	while (true)
	{
		// 플레이어 턴
		while (true)
		{
			system("cls");
			player->Print();
			dealer->Print();
			if (player->Calculate() >= 21) break;
			printf("[ 1. Hit ] [ 2. Stand ] \n");
			printf("입력 : ");
			scanf_s("%i", &Input);

			if (Input == 1)
			{
				player->Draw(Deck);
				continue;
			}
			else if (Input == 2) break;
			else
			{
				printf("값을 잘못 입력했습니다. \n");
				Sleep(500);
				continue;
			}
		}
		if (player->Calculate() == 21)
		{
			cout << "Player BlackJack ! " << endl;
			break;
		}
		else if (player->Calculate() > 21)
		{
			cout << "Player Lose" << endl;
			break;
		}

		// 딜러 턴
		while (true)
		{
			system("cls");
			dealer->Print();
			player->Print();
			if (dealer->Calculate() >= 17) break;

			dealer->Draw(Deck);

			Sleep(500);
		}
		if (dealer->Calculate() > 21)
			cout << "Dealer Lose" << endl;
		else if (dealer->Calculate() == 21)
			cout << "Dealer BlackJack ! " << endl;
		else if (player->Calculate() > dealer->Calculate())
			cout << "Player Win ! " << endl;
		else if (player->Calculate() < dealer->Calculate())
			cout << "Dealer Win !" << endl;

		break;
	}


	delete player;
	player = nullptr;
	delete dealer;
	dealer = nullptr;
	delete[] Deck;
	Deck = nullptr;
	
	return 0;
}