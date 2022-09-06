#include <iostream>
#include <time.h>
#include <string>

using namespace std;

enum JOKBO
{
	KK_0,
	KK_9,
	DD_1 = 11,
	DD_10 = 20,
	KD
};

struct HWA2
{
	int month;
	string shape;
};

struct PLAYER
{
	string name;
	int money;
	//°á°ú
	int jokbo;
	//ÆÐ
	HWA2 card[2];
};

void Swap(int start, int dest, HWA2* deck)
{
	HWA2 temp = deck[start];
	deck[start] = deck[dest];
	deck[dest] = temp;
}

void Shuffle(HWA2* deck)
{
	for (int i = 0; i < 1000; i++)
	{
		int start = rand() % 20;
		int dest = rand() % 20;
		Swap(start, dest, deck);
	}
}

void Print(PLAYER* players, int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << players[i].name << "\t" <<
			players[i].card[0].month << players[i].card[0].shape << "\t" <<
			players[i].card[1].month << players[i].card[1].shape << "\t" <<
			players[i].money << "\t";

		if (players[i].jokbo == KD)
		{
			cout << players[i].card[0].month << players[i].card[1].month <<
				"±¤¶¯" << endl;
		}
		else if (players[i].jokbo < DD_1) //²ý
		{
			cout << players[i].jokbo << "²ý" << endl;
		}
		else //¶¯
		{
			cout << (players[i].jokbo - 10) << "¶¯" << endl;
		}
	}
}

void MakeJokbo(int num, PLAYER* players)
{
	for (int i = 0; i < num; i++)
	{
		//±¤¶¯
		if (players[i].card[0].shape == "±¤" &&
			players[i].card[1].shape == "±¤")
		{
			players[i].jokbo = KD;
		}

		//¶¯
		else if (players[i].card[0].month == players[i].card[1].month)
		{
			//									Ä«µå ¿ù¼ö	10
			players[i].jokbo = players[i].card[0].month + (DD_1 - 1);
		}
		else
		{
			players[i].jokbo = (players[i].card[0].month + players[i].card[1].month) % 10;
		}
	}
}


int main()
{
	srand(time(NULL));

	int num;

	while (true)
	{
		cout << "ÇÃ·¹ÀÌ¾î ¼ö¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä : ";
		cin >> num;

		if (num > 10)
			cout << "´Ù½Ã ÀÔ·Â" << endl;
		else
			break;
	}

	PLAYER* players;
	players = new PLAYER[num];

	//ÃÊ±âÈ­
	for (int i = 0; i < num; i++)
	{
		string name;

		cout << (i + 1) << "ÀÌ¸§À» ÀÔ·Â : ";
		cin >> name;

		players[i].name = name;
		players[i].money = 10000;
	}

	//µ¦ ¸¸µé±â
	HWA2 deck[20];

	//µ¦ ÃÊ±âÈ­
	for (int i = 0; i < 20; i++)
	{
		deck[i].month = i % 10 + 1;
		deck[i].shape = "ÇÇ";
	}
	deck[0].shape = deck[2].shape = deck[7].shape = "±¤";

	int start = 0;
	while (not start)
	{
		//¼ÅÇÃ
		Shuffle(deck);

		//ÆÐ ³ª´²ÁÖ±â
		for (int i = 0; i < num; i++)
		{
			players[i].card[0] = deck[i];
			players[i].card[1] = deck[i + 10];
		}

		//°á°ú -> Á·º¸
		MakeJokbo(num, players);

		//½Â¸®ÀÚ -> ÃÖ´ë°ª
		int max = KK_0;
		for (int i = 0; i < num; i++)
		{
			//ÃÖ´ë°ª °»½Å
			if (players[i].jokbo > max)
			{
				max = players[i].jokbo;
			}
		}

		for (int i = 0; i < num; i++)
		{
			if (max == players[i].jokbo)
			{
				cout << players[i].name << "½Â¸®" << endl;
			}
		}



		//µ· ³ª´²ÁÖ°í

		Print(players, num);

		cout << "0. °è¼Ó 1. ³ª°¡±â" << endl;
		cin >> start;
	}






	return 0;
}