#include <iostream>
using namespace std;

typedef unsigned long long BLONG;

BLONG Dynamic_Fibonacci(int n)
{
	if (n == 0 || n == 1)
		return n;

	BLONG* table = new BLONG[n + 1];

	table[0] = 0;
	table[1] = 1;

	for (int i=2; i<=n; i++)
	{
		table[i] = table[i - 1] + table[i - 2];
	}

	BLONG result = table[n];
	delete[] table;

	return result;
}

int main()
{
	cout << Dynamic_Fibonacci(10) << endl;
}