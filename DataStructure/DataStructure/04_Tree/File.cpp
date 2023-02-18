#include <Windows.h>
#include <stdio.h>
#include <time.h>

void main()
{
	srand((UINT)time(0));

	FILE* file;
	fopen_s(&file, "Data.txt", "w");
	{
		for (int i = 0; i < USHRT_MAX; i++)
			fprintf(file, "%d %d\n", i, rand());
	}
	fclose(file);
}