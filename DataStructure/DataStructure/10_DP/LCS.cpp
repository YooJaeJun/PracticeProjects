#include <stdio.h>
#include <string.h>

struct Table
{
	int** Data;
};

int LCS(char* x, char* y, int i, int j, Table* table)
{
	if (i == 0 || j == 0)
	{
		table->Data[i][j] = 0;

		//printf("%d, i == %d, j == %d, %c == %c\n", table->Data[i][j], i, j, x[i - 1], y[j - 1]);
	}
	else if (x[i - 1] == y[j - 1])
	{
		table->Data[i][j] = LCS(x, y, i - 1, j - 1, table) + 1;

		//printf("%d, i == %d, j == %d, %c == %c\n", table->Data[i][j], i, j, x[i - 1], y[j - 1]);
	}
	else
	{
		int a = LCS(x, y, i - 1, j, table);
		int b = LCS(x, y, i, j - 1, table);

		if (a > b)
			table->Data[i][j] = a;
		else
			table->Data[i][j] = b;

		//printf("%d, i == %d, j == %d, %c == %c\n", table->Data[i][j], i, j, x[i - 1], y[j - 1]);
	}

	return table->Data[i][j];
}

int main()
{
	char* a = "GOOD MORNING.";
	char* b = "GUTEN MORGEN.";

	//char* a = "ABC";
	//char* b = "EBF";

	int lenA = strlen(a);
	int lenB = strlen(b);

	Table table;
	table.Data = new int* [lenA + 1];

	for (int i = 0; i < lenA + 1; i++)
	{
		table.Data[i] = new int[lenB + 1];
		memset(table.Data[i], 0, sizeof(int) * (lenB + 1));
	}

	int result = LCS(a, b, lenA, lenB, &table);

	printf("\n%-04s", " ");

	for (int i = 0; i <= lenA; i++)
		printf("%c ", b[i]);
	printf("\n");

	for (int i = 0; i <= lenA; i++)
	{
		printf("%c ", a[i - 1]);

		for (int j = 0; j <= lenB; j++)
			printf("%d ", table.Data[i][j]);

		printf("\n");
	}

	printf("%d", result);

	return 0;
}