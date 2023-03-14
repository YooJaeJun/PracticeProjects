#include <stdio.h>
#include <string.h>

#define MAX 1024
#define INIT -1

#define START 'S'
#define GOAL 'G'
#define WAY ' '
#define WALL '#'
#define MARKED '+'

enum class Direction
{
	North = 0, South, East, West
};

struct Position
{
	int X, Y;
};

struct MazeDesc
{
	int Columns;
	int Rows;

	char** Data;
};

void ReadMaze(char* path, MazeDesc* desc)
{
	FILE* fp;
	fopen_s(&fp, path, "r");

	int rows = 0, columns = INIT;
	char buffer[MAX];

	while (fgets(buffer, MAX, fp) != NULL)
	{
		rows++;

		if (columns == INIT)
			columns = (int)strlen(buffer) - 1;
	}

	desc->Rows = rows;
	desc->Columns = columns;
	desc->Data = new char* [rows];

	for (int i = 0; i < rows; i++)
		desc->Data[i] = new char[columns];

	rewind(fp);

	for (int i = 0; i < rows; i++)
	{
		fgets(buffer, MAX, fp);

		for (int j = 0; j < columns; j++)
			desc->Data[i][j] = buffer[j];
	}
	fclose(fp);
}

bool GetNextStep(MazeDesc* desc, Position* curr, Direction direction, Position* next)
{
	switch (direction)
	{
	case Direction::North:
	{
		next->X = curr->X;
		next->Y = curr->Y - 1;

		if (next->Y == -1)
			return false;
	}
	break;

	case Direction::South:
	{
		next->X = curr->X;
		next->Y = curr->Y + 1;

		if (next->Y == desc->Rows)
			return false;
	}
	break;

	case Direction::East:
	{
		next->X = curr->X + 1;
		next->Y = curr->Y;

		if (next->X == desc->Columns)
			return false;
	}
	break;

	case Direction::West:
	{
		next->X = curr->X - 1;
		next->Y = curr->Y;

		if (next->X == -1)
			return false;
	}
	break;
	}

	if (desc->Data[next->Y][next->X] == WALL) return false;
	if (desc->Data[next->Y][next->X] == MARKED) return false;

	return true;
}

bool MoveTo(MazeDesc* desc, Position* curr, Direction direction)
{
	Position next;

	if (desc->Data[curr->Y][curr->X] == GOAL)
		return true;

	desc->Data[curr->Y][curr->X] = MARKED;

	for (int i = 0; i < 4; i++)
	{
		if (GetNextStep(desc, curr, (Direction)i, &next) == false)
			continue;

		if (MoveTo(desc, &next, Direction::North) == true)
			return true;
	}

	desc->Data[curr->Y][curr->X] = WAY;

	return false;
}

bool Solve(MazeDesc* desc)
{
	bool startFound = false;
	bool result = false;

	Position start;
	for (int y = 0; y < desc->Rows; y++)
	{
		for (int x = 0; x < desc->Columns; x++)
		{
			if (desc->Data[y][x] == START)
			{
				start.X = x;
				start.Y = y;
				startFound = true;

				break;
			}//if(desc)
		}//for(x)
	}//for(y)
	if (startFound == false)
	{
		printf("##########\n");

		return false;
	}

	result |= MoveTo(desc, &start, Direction::North);
	result |= MoveTo(desc, &start, Direction::South);
	result |= MoveTo(desc, &start, Direction::East);
	result |= MoveTo(desc, &start, Direction::West);

	desc->Data[start.Y][start.X] = START;

	return result;
}

int main()
{
	char* path = "MazeSample.txt";

	MazeDesc desc;
	ReadMaze(path, &desc);

	if (Solve(&desc) == false)
		return 0;

	for (int y = 0; y < desc.Rows; y++)
	{
		for (int x = 0; x < desc.Columns; x++)
		{
			printf("%c", desc.Data[y][x]);
		}

		printf("\n");
	}

	return 0;
}