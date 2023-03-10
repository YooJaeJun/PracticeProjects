#include <iostream>
using namespace std;

void Merge(int datas[], int start, int mid, int end)
{
	int left = start;
	int right = mid + 1;

	int destIndex = 0;
	int* dest = new int[(end - start + 1)];

	while (left <= mid && right <= end)
	{
		if (datas[left] < datas[right])
		{
			dest[destIndex] = datas[left];
			left++;
		}
		else
		{
			dest[destIndex] = datas[right];
			right++;
		}

		destIndex++;
	}

	while (left <= mid)
		dest[destIndex++] = datas[left++];

	while (right <= end)
		dest[destIndex++] = datas[right++];

	destIndex = 0;
	for (int i = start; i <= end; i++)
		datas[i] = dest[destIndex++];

	delete[] dest;
}

void MergeSort(int datas[], int start, int end)
{
	if (end - start < 1)
		return;

	int mid = (start + end) / 2;

	MergeSort(datas, start, mid);
	MergeSort(datas, mid + 1, end);

	Merge(datas, start, mid, end);
}

int main()
{
	int datas[] = { 5,1,6,4,8,3,7,9,2 };
	int count = sizeof(datas) / sizeof(datas[0]);

	for (int i = 0; i < count; i++)
		cout << datas[i] << ' ';
	cout << endl;

	MergeSort(datas, 0, count - 1);

	for (int i = 0; i < count; i++)
		cout << datas[i] << ' ';
	cout << endl;

	return 0;
}