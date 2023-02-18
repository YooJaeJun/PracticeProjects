#include <Windows.h>
#include <stdio.h>
#include "BinarySearch.h"
#include "Timer.h"

struct Data
{
	UINT Index;
	UINT Score;
};

void ReadData(Data* data)
{
	FILE* file;
	fopen_s(&file, "Data.txt", "r");
	{
		for (UINT i = 0; i < USHRT_MAX; i++)
			fscanf_s(file, "%d %d", &data[i].Index, &data[i].Score);
	}
	fclose(file);
}

Data* SequenceSearch(Data* datas, UINT size, UINT target, OUT UINT* count)
{
	*count = 0;
	Data* result = NULL;

	for (UINT i = 0; i < USHRT_MAX; i++)
	{
		if (target == datas[i].Index)
		{
			*count = i;
			result = &datas[i];

			break;
		}
	}

	return result;
}

Data* BinarySearch(Data* datas, UINT size, UINT target, OUT UINT* count)
{
	*count = 0;
	
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (datas[middle].Index == target)
			return &datas[middle];
		else if (target > datas[middle].Index)
			left = middle + 1;
		else if (target < datas[middle].Index)
			right = middle - 1;

		*count = (*count) + 1;
	}
	
	return NULL;
}

int BinaryCompareCount = 0;
int BinaryCompare(const void* val1, const void* val2)
{
	Data* data1 = (Data*)val1;
	Data* data2 = (Data*)val2;

	BinaryCompareCount++;

	if (data1->Index > data2->Index)
		return 1;
	else if (data1->Index < data2->Index)
		return -1;
	
	return 0;
}

int main()
{
	Data datas[USHRT_MAX];
	ReadData(datas);

	//for (int i = 0; i < USHRT_MAX; i++)
	//	printf("%d, %d\n", data[i].Index, data[i].Score);

	UINT count = 0;
	UINT target = 60000;

	Timer timer;
	// SequenceSearch
	{
		timer.Start();
		Data* result = SequenceSearch(datas, USHRT_MAX, target, &count);
		timer.End();
	}
	printf("순차 탐색 %d번에 찾음, 시간 : %f\n", count, timer.RunningTime());
	// BinarySearch
	{
		timer.Start();
		Data* result = BinarySearch(datas, USHRT_MAX, target, &count);
		timer.End();
	}
	printf("이진 탐색 %d번에 찾음, 시간 : %f\n", count, timer.RunningTime());
	// STL BinarySearch
	{
		timer.Start();
		bsearch((void*)&target, (void*)datas, USHRT_MAX, sizeof(Data), BinaryCompare);
		timer.End();
	}
	printf("STL 이진 탐색 %d번에 찾음, 시간 : %f\n", BinaryCompareCount, timer.RunningTime());

	return 0;
}