#include "SampleClass.h"

int main()
{
	// �⺻ ������ (Default Constructor)
	// ����ڰ� �����ڸ� �������� ���� �� �����Ϸ��� �ڵ������� �����ϴ� �������Դϴ�.
	// ���� �����ڸ� ������ ��� �����Ϸ��� �⺻ �����ڸ� �������� �ʽ��ϴ�.
#ifndef DEFAULT
	SampleClass sample = SampleClass();
	sample.Print();
#endif

	SampleClass sample_1 = SampleClass(3, 4);
	sample_1.Print();


	return 0;
}