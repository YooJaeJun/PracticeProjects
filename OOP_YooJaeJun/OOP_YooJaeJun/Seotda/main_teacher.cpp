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
	//���
	int jokbo;
	//��
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
				"����" << endl;
		}
		else if (players[i].jokbo < DD_1) //��
		{
			cout << players[i].jokbo << "��" << endl;
		}
		else //��
		{
			cout << (players[i].jokbo - 10) << "��" << endl;
		}
	}
}

void MakeJokbo(int num, PLAYER* players)
{
	for (int i = 0; i < num; i++)
	{
		//����
		if (players[i].card[0].shape == "��" &&
			players[i].card[1].shape == "��")
		{
			players[i].jokbo = KD;
		}

		//��
		else if (players[i].card[0].month == players[i].card[1].month)
		{
			//									ī�� ����	10
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
		cout << "�÷��̾� ���� �Է����ּ��� : ";
		cin >> num;

		if (num > 10)
			cout << "�ٽ� �Է�" << endl;
		else
			break;
	}

	PLAYER* players;
	players = new PLAYER[num];

	//�ʱ�ȭ
	for (int i = 0; i < num; i++)
	{
		string name;

		cout << (i + 1) << "�̸��� �Է� : ";
		cin >> name;

		players[i].name = name;
		players[i].money = 10000;
	}

	//�� �����
	HWA2 deck[20];

	//�� �ʱ�ȭ
	for (int i = 0; i < 20; i++)
	{
		deck[i].month = i % 10 + 1;
		deck[i].shape = "��";
	}
	deck[0].shape = deck[2].shape = deck[7].shape = "��";

	int start = 0;
	while (not start)
	{
		//����
		Shuffle(deck);

		//�� �����ֱ�
		for (int i = 0; i < num; i++)
		{
			players[i].card[0] = deck[i];
			players[i].card[1] = deck[i + 10];
		}

		//��� -> ����
		MakeJokbo(num, players);

		//�¸��� -> �ִ밪
		int max = KK_0;
		for (int i = 0; i < num; i++)
		{
			//�ִ밪 ����
			if (players[i].jokbo > max)
			{
				max = players[i].jokbo;
			}
		}

		for (int i = 0; i < num; i++)
		{
			if (max == players[i].jokbo)
			{
				cout << players[i].name << "�¸�" << endl;
			}
		}



		//�� �����ְ�

		Print(players, num);

		cout << "0. ��� 1. ������" << endl;
		cin >> start;
	}






	return 0;
}