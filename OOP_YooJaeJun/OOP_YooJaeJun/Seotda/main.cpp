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
	cout << "Ÿ¶ÀçÁØÀÇ Áñ°Å¿î ¼¸´Ù °ÔÀÓ\n";
	cout << "-----------------------------\n";
	cout << "1. ÃÖÃÊ °¢°¢ 10,000¿ø¾¿ Áö±Ş\n";
	cout << "2. ÇÑ ÆÇ´ç 500¿ø¾¿ Â÷°¨\n";
	cout << "3. ¿ì½Â ½Ã ÇÑ ÆÇ µ· ¸ô¾ÆÁÖ±â\n";
	cout << "4. µ¿ÀÏ ÆĞÀÏ ½Ã ¼±ÅÏÀÌ ½Â¸®\n";
	cout << "5. Æ¯¼ö ±â´É Á·º¸ ¾øÀ½\n";
	cout << "6. ÇÃ·¹ÀÌ¾î ¼ö: 2 ~ 10\n";
	cout << "-----------------------------\n";

	cout << "ÇÃ·¹ÀÌ¾î ¼ö : ";
	int n;
	cin >> n;
	while (n <= 1 || n > 10)
	{
		cout << "2ÀÌ»ó 10ÀÌÇÏÀÇ ¼ö¸¸ ÀÔ·ÂÇÏ¼¼¿ä.\n";
		cin >> n;
	}

	vector<Player> players(n);
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << "¹øÂ° ÀÌ¸§ : ";
		cin >> players[i].name;
	}

	vector<string> cards{ "1ÎÃ", "1êÅ", "2êÅ", "2êÅ", "3ÎÃ", "3êÅ", "4êÅ", "4êÅ", "5êÅ", "5êÅ",
		"6êÅ", "6êÅ", "7êÅ", "7êÅ", "8ÎÃ", "8êÅ", "9êÅ", "9êÅ", "10êÅ", "10êÅ" };

	unordered_map<string, int> result;
	result["»ïÆÈ±¤¶¯"] = 1;
	result["±¤¶¯"] = 2;
	result["10¶¯"] = 3;
	result["9¶¯"] = 4;
	result["8¶¯"] = 5;
	result["7¶¯"] = 6;
	result["6¶¯"] = 7;
	result["5¶¯"] = 8;
	result["4¶¯"] = 9;
	result["3¶¯"] = 10;
	result["2¶¯"] = 11;
	result["1¶¯"] = 12;
	result["¾Ë¸®"] = 13;
	result["µ¶»ç"] = 14;
	result["±¸»æ"] = 15;
	result["Àå»æ"] = 16;
	result["Àå»ç"] = 17;
	result["¼¼·ú"] = 18;
	result["°©¿À"] = 19;
	result["8²ı"] = 20;
	result["7²ı"] = 21;
	result["6²ı"] = 22;
	result["5²ı"] = 23;
	result["4²ı"] = 24;
	result["3²ı"] = 25;
	result["2²ı"] = 26;
	result["1²ı"] = 27;
	result["¸ÁÅë"] = 28;

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

			if ((c0 == "3ÎÃ" && c1 == "8ÎÃ") || (c0 == "8ÎÃ" && c1 == "3ÎÃ"))
				players[i].result = "»ïÆÈ±¤¶¯";

			else if ((c0 == "1ÎÃ" && c1 == "3ÎÃ") || (c0 == "3ÎÃ" && c1 == "1ÎÃ") ||
				(c0 == "1ÎÃ" && c1 == "8ÎÃ") || (c0 == "8ÎÃ" && c1 == "1ÎÃ"))
				players[i].result = "±¤¶¯";

			else if (c0PopInt == 10 && c1PopInt == 10)
				players[i].result = "10¶¯";

			else if (c0PopInt == 9 && c1PopInt == 9)
				players[i].result = "9¶¯";

			else if (c0PopInt == 8 && c1PopInt == 8)
				players[i].result = "8¶¯";

			else if (c0PopInt == 7 && c1PopInt == 7)
				players[i].result = "7¶¯";

			else if (c0PopInt == 6 && c1PopInt == 6)
				players[i].result = "6¶¯";

			else if (c0PopInt == 5 && c1PopInt == 5)
				players[i].result = "5¶¯";

			else if (c0PopInt == 4 && c1PopInt == 4)
				players[i].result = "4¶¯";

			else if (c0PopInt == 3 && c1PopInt == 3)
				players[i].result = "3¶¯";

			else if (c0PopInt == 2 && c1PopInt == 2)
				players[i].result = "2¶¯";

			else if (c0PopInt == 1 && c1PopInt == 1)
				players[i].result = "1¶¯";

			else if ((c0PopInt == 1 && c1PopInt == 2) || (c0PopInt == 2 && c1PopInt == 1))
				players[i].result = "¾Ë¸®";

			else if ((c0PopInt == 1 && c1PopInt == 4) || (c0PopInt == 4 && c1PopInt == 1))
				players[i].result = "µ¶»ç";

			else if ((c0PopInt == 1 && c1PopInt == 9) || (c0PopInt == 9 && c1PopInt == 1))
				players[i].result = "±¸»æ";

			else if ((c0PopInt == 1 && c1PopInt == 10) || (c0PopInt == 10 && c1PopInt == 1))
				players[i].result = "Àå»æ";

			else if ((c0PopInt == 4 && c1PopInt == 10) || (c0PopInt == 10 && c1PopInt == 4))
				players[i].result = "Àå»ç";

			else if ((c0PopInt == 4 && c1PopInt == 6) || (c0PopInt == 6 && c1PopInt == 4))
				players[i].result = "¼¼·ú";

			else if ((c0PopInt + c1PopInt) % 10 == 9)
				players[i].result = "°©¿À";

			// else if ((c0PopInt == 2 && c1PopInt == 8) || (c0PopInt == 8 && c1PopInt == 2))
			else if ((c0PopInt + c1PopInt) % 10 == 0)
				players[i].result = "¸ÁÅë";

			else
				players[i].result = to_string((c0PopInt + c1PopInt) % 10) + "²ı";

			players[i].rank = result[players[i].result];
		}

		sort(players.begin(), players.end());
		players[0].money += n * 500;

		cout << "---------------------------------------------------------------------------------------------\n";
		cout << "[" << players[0].name << "]" << ' ' << " ½Â¸®!!! \n\n";

		cout << "ÀÌ¸§\t\t" << "Ä«µå1\t\t" << "Ä«µå2\t\t" << "µ·\t\t" << "ÆĞ\t\t" << "¼øÀ§\n";
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

		cout << "\n0. °è¼Ó  /  1. ³ª°¡±â \n";
		int ans;
		cin >> ans;
		if (ans) break;
	}
}