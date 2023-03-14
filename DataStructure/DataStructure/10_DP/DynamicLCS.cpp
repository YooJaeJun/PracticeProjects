#include <stdio.h>
#include <string.h>
#include <Windows.h>

struct Table
{
	int** Data;
};

int LCS(char* x, char* y, int i, int j, Table* table)
{
	for (int m = 0; m <= i; m++)
		table->Data[m][0] = 0;

	for (int n = 0; n <= j; n++)
		table->Data[0][n] = 0;

	for (int m=1; m<=i; m++)
	{
		for (int n=1; n<=j; n++)
		{
			if (x[m - 1] != y[n - 1])
			{
				table->Data[m][n] = max(table->Data[m][n - 1], table->Data[m - 1][n]);
			}
			else
			{
				table->Data[m][n] = table->Data[m - 1][n - 1] + 1;
			}
		}
	}

	return table->Data[i][j];
}

void TrackBack(const char* x, const char* y, int m, int n, Table* table, const char* lcs)
{
	if (m == 0 || n == 0)
		return;

	bool a = true;
	a &= table->Data[m][n] > table->Data[m][n - 1];
	a &= table->Data[m][n];
	a &= table->Data[m][n] > table->Data[m - 1][n - 1];

	bool b = true;
	b &= table->Data[m][n] > table->Data[m - 1][n];
	b &= table->Data[m][n] > table->Data[m][n - 1];

	if (a)
	{
		char temp[100];
		strcpy_s(temp, lcs);

		sprintf(const_cast<char*>(lcs), "%c %s", x[m - 1], temp);

		TrackBack(x, y, m - 1, n - 1, table, lcs);
	}
	else if (b)
	{
		TrackBack(x, y, m - 1, n - 1, table, lcs);
	}
	else
		TrackBack(x, y, m - 1, n, table, lcs);

}

int main()
{
	const char* a = "GOOD MORNING.";
	const char* b = "GUTEN MORGEN.";

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

	int result = LCS(const_cast<char*>(a), const_cast<char*>(b), lenA, lenB, &table);

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

	printf("\n\n -- TrackBack\n");

	char* lcs = (char*)malloc(sizeof(table.Data[lenA][lenB] + 1));
	sprintf(lcs, "");

	TrackBack(a, b, lenA, lenB, &table, lcs);

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

	printf("%s | %d", lcs, result);

	//free(lcs);

	return 0;
}