#include <Windows.h>
#include <stdio.h>
using namespace std;

void Sort(int* datas, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (datas[i - 1] <= datas[i])
			continue;

		int value = datas[i];
		for (int k = 0; k < i; k++)
		{
			if (datas[k] > value)
			{
				memmove(&datas[k + 1], &datas[k], (i - k) * sizeof(datas[0]));
				datas[k] = value;

				break;
			}
		}//for(k)
	}//for(i)
}

int main()
{
	int datas[] = { 5,1,6,4,2,3 };
	int length = sizeof(datas) / sizeof(datas[0]);
	Sort(datas, length);

	for (int i = 0; i < length; i++)
	{
		printf("%d ", datas[i]);
	}
	printf("\n\n");

	return 0;
}