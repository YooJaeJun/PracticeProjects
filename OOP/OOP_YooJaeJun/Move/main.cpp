#include <iostream>
#include <random>
using namespace std;

int main()
{
	srand(time(nullptr));

	const int n = 5;
	const int n2 = n * n;
	int arr[n2] = { 0 };

	for (int i = 0; i < n2; i++)
	{
		arr[i] = i;
	}
	random_shuffle(arr, arr + n2);
	int grid[n][n] = { 0 };

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			grid[r][c] = arr[r * n + c];
		}
	}
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			if (grid[r][c] == 0)
			{
				swap(grid[r][c], grid[n - 1][n - 1]);
			}
		}
	}


	int curR = n - 1, curC = n - 1;
	while (1)
	{
		cout << "\n";
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < n; c++)
			{
				printf("%5d", grid[r][c]);
			}
			cout << "\n\n";
		}

		cout << "           8.위\n";
		cout << "   4.왼쪽        6.오른쪽\n";
		cout << "          2.아래\n";

		bool moveFlag = true;
		int input;
		cin >> input;
		switch (input)
		{
		case 8:
			if (curR > 0)
			{
				swap(grid[curR][curC], grid[curR - 1][curC]);
				curR--;
			}
			else moveFlag = false;
			break;
		case 2:
			if (curR < n - 1)
			{
				swap(grid[curR][curC], grid[curR + 1][curC]);
				curR++;
			}
			else moveFlag = false;
			break;
		case 4:
			if (curC > 0)
			{
				swap(grid[curR][curC], grid[curR][curC - 1]);
				curC--;
			}
			else moveFlag = false;
			break;
		case 6:
			if (curC < n - 1)
			{
				swap(grid[curR][curC], grid[curR][curC + 1]);
				curC++;
			}
			else moveFlag = false;
			break;
		default:
			cout << "똑바로 입력하라구!!!\n";
			break;
		}

		if (moveFlag == false)
		{
			cout << "그 방향으론 더 이상 갈 수 업다구~\n";
		}
	}
}