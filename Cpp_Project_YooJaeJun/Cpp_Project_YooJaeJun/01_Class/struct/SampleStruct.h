#pragma once
#include <iostream>
using namespace std;

struct SampleStruct
{
	// struct �� ���� ��� ���������ڸ� ������� �ʴ´ٸ� ������� public �� �˴ϴ�.
	int Public = 0;

private :	// �Ʒ��� ��� ����� �ܺο��� ������ �� ���� ����� �����մϴ�.
	int A = 10;

	void Print();

public :	// �Ʒ��� ��� ����� �ܺο��� ������ �� �ִ� ����� �����մϴ�.
	int B = 20;
};

