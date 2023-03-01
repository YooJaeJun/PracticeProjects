#include <stdio.h>
#include <algorithm>
#include "../Timer.h"
using namespace std;

struct Data
{
	UINT Number;
	UINT Score;
};

void ReadData(Data* datas)
{
	FILE* file;
	fopen_s(&file, "Data.txt", "r");

	for (int i = 0; i < USHRT_MAX; i++)
		fscanf_s(file, "%d %d", &datas[i].Number, &datas[i].Score);

	fclose(file);
}

void WriteData(Data* datas)
{
	FILE* file;
	fopen_s(&file, "ResultData.txt", "w");

	for (int i = 0; i < USHRT_MAX; i++)
		fprintf_s(file, "%d, %d\n", datas[i].Number, datas[i].Score);

	fclose(file);
}

void Swap(Data* a, Data* b)
{
	Data temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(Data* datas, int left, int right)
{
	UINT first = left;
	UINT pivot = datas[first].Score;

	left++;
	while (left <= right)
	{
		while (datas[left].Score <= pivot && left < right)
			left++;

		while (datas[right].Score > pivot && left <= right)
			right--;

		if (left < right)
		{
			Swap(&datas[left], &datas[right]);
		}
		else
			break;
	}

	Swap(&datas[first], &datas[right]);

	return right;
}

void Sort(Data* datas, int left, int right)
{
	if (left < right)
	{
		int index = Partition(datas, left, right);

		Sort(datas, left, index - 1);
		Sort(datas, index + 1, right);
	}
}

int Compare(const void* val1, const void* val2)
{
	Data* data1 = (Data*)val1;
	Data* data2 = (Data*)val2;

	if (data1->Score > data2->Score)
		return 1;
	else if (data1->Score < data2->Score)
		return -1;
	
	return 0;
}

bool Compare2(const Data& val1, const Data& val2)
{
	return val1.Score > val2.Score;
}

int main()
{
	Data datas[USHRT_MAX];
	ReadData(datas);

	Timer timer;


	timer.Start();
	{
		Sort(datas, 0, USHRT_MAX - 1);
	}
	timer.End();
	printf("1 : %f\n", timer.RunningTime());


	timer.Start();
	{
		qsort(datas, USHRT_MAX, sizeof(Data), Compare);
	}
	timer.End();
	printf("2 : %f\n", timer.RunningTime());


	timer.Start();
	{
		std::sort(datas, datas + USHRT_MAX, Compare2);
	}
	timer.End();
	printf("3 : %f\n", timer.RunningTime());


	// WriteData(datas);

	return 0;
}