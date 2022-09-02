#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
using namespace std;

class Player
{
public:
	string	name;
	string	card[2];
	int		money = 10000;
	string  result;
	int		rank;
public:
	bool operator<(const Player& other)
	{
		return rank < other.rank;
	}
};

int main()
{
	srand(time(nullptr));

	cout << "-----------------------------\n";
	cout << "�������� ��ſ� ���� ����\n";
	cout << "-----------------------------\n";
	cout << "1. ���� ���� 10,000���� ����\n";
	cout << "2. �� �Ǵ� 500���� ����\n";
	cout << "3. ��� �� �� �� �� �����ֱ�\n";
	cout << "4. ���� ���� �� ������ �¸�\n";
	cout << "5. Ư�� ��� ���� ����\n";
	cout << "6. �÷��̾� ��: 2 ~ 10\n";
	cout << "-----------------------------\n";

	cout << "�÷��̾� �� : ";
	int n;
	cin >> n;
	while (n <= 1 || n > 10)
	{
		cout << "2�̻� 10������ ���� �Է��ϼ���.\n";
		cin >> n;
	}

	vector<Player> players(n);
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << "��° �̸� : ";
		cin >> players[i].name;
	}

	vector<string> cards{ "1��", "1��", "2��", "2��", "3��", "3��", "4��", "4��", "5��", "5��",
		"6��", "6��", "7��", "7��", "8��", "8��", "9��", "9��", "10��", "10��" };

	unordered_map<string, int> result;
	result["���ȱ���"] = 1;
	result["����"] = 2;
	result["10��"] = 3;
	result["9��"] = 4;
	result["8��"] = 5;
	result["7��"] = 6;
	result["6��"] = 7;
	result["5��"] = 8;
	result["4��"] = 9;
	result["3��"] = 10;
	result["2��"] = 11;
	result["1��"] = 12;
	result["�˸�"] = 13;
	result["����"] = 14;
	result["����"] = 15;
	result["���"] = 16;
	result["���"] = 17;
	result["����"] = 18;
	result["����"] = 19;
	result["8��"] = 20;
	result["7��"] = 21;
	result["6��"] = 22;
	result["5��"] = 23;
	result["4��"] = 24;
	result["3��"] = 25;
	result["2��"] = 26;
	result["1��"] = 27;
	result["����"] = 28;

	while (1)
	{
		random_shuffle(cards.begin(), cards.end());

		for (int i = 0; i < n; i++)
		{
			string c0 = players[i].card[0] = cards[i * 2];
			string c1 = players[i].card[1] = cards[i * 2 + 1];

			string c0Pop = c0;
			string c1Pop = c1;
			c0Pop.pop_back();
			c1Pop.pop_back();
			int c0PopInt = stoi(c0Pop); 
			int c1PopInt = stoi(c1Pop);

			if ((c0 == "3��" && c1 == "8��") || (c0 == "8��" && c1 == "3��"))
				players[i].result = "���ȱ���";

			else if ((c0 == "1��" && c1 == "3��") || (c0 == "3��" && c1 == "1��") ||
				(c0 == "1��" && c1 == "8��") || (c0 == "8��" && c1 == "1��"))
				players[i].result = "����";

			else if (c0PopInt == 10 && c1PopInt == 10)
				players[i].result = "10��";

			else if (c0PopInt == 9 && c1PopInt == 9)
				players[i].result = "9��";

			else if (c0PopInt == 8 && c1PopInt == 8)
				players[i].result = "8��";

			else if (c0PopInt == 7 && c1PopInt == 7)
				players[i].result = "7��";

			else if (c0PopInt == 6 && c1PopInt == 6)
				players[i].result = "6��";

			else if (c0PopInt == 5 && c1PopInt == 5)
				players[i].result = "5��";

			else if (c0PopInt == 4 && c1PopInt == 4)
				players[i].result = "4��";

			else if (c0PopInt == 3 && c1PopInt == 3)
				players[i].result = "3��";

			else if (c0PopInt == 2 && c1PopInt == 2)
				players[i].result = "2��";

			else if (c0PopInt == 1 && c1PopInt == 1)
				players[i].result = "1��";

			else if ((c0PopInt == 1 && c1PopInt == 2) || (c0PopInt == 2 && c1PopInt == 1))
				players[i].result = "�˸�";

			else if ((c0PopInt == 1 && c1PopInt == 4) || (c0PopInt == 4 && c1PopInt == 1))
				players[i].result = "����";

			else if ((c0PopInt == 1 && c1PopInt == 9) || (c0PopInt == 9 && c1PopInt == 1))
				players[i].result = "����";

			else if ((c0PopInt == 1 && c1PopInt == 10) || (c0PopInt == 10 && c1PopInt == 1))
				players[i].result = "���";

			else if ((c0PopInt == 4 && c1PopInt == 10) || (c0PopInt == 10 && c1PopInt == 4))
				players[i].result = "���";

			else if ((c0PopInt == 4 && c1PopInt == 6) || (c0PopInt == 6 && c1PopInt == 4))
				players[i].result = "����";

			else if ((c0PopInt + c1PopInt) % 10 == 9)
				players[i].result = "����";

			// else if ((c0PopInt == 2 && c1PopInt == 8) || (c0PopInt == 8 && c1PopInt == 2))
			else if ((c0PopInt + c1PopInt) % 10 == 0)
				players[i].result = "����";

			else
				players[i].result = to_string((c0PopInt + c1PopInt) % 10) + "��";

			players[i].rank = result[players[i].result];
		}

		sort(players.begin(), players.end());
		players[0].money += n * 500;

		cout << "---------------------------------------------------------------------------------------------\n";
		cout << "[" << players[0].name << "]" << ' ' << " �¸�!!! \n\n";

		cout << "�̸�\t\t" << "ī��1\t\t" << "ī��2\t\t" << "��\t\t" << "��\t\t" << "����\n";
		for (int i = 0; i < n; i++)
		{
			players[i].money -= 500;

			cout << players[i].name << "\t\t" <<
				players[i].card[0] << "\t\t" <<
				players[i].card[1] << "\t\t" <<
				players[i].money << "\t\t" << 
				players[i].result << "\t\t" <<
				i + 1 << '\n';
		}

		cout << "\n0. ���  /  1. ������ \n";
		int ans;
		cin >> ans;
		if (ans) break;
	}
}