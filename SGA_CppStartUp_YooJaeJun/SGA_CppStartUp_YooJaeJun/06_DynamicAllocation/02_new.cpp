#include <iostream>
using namespace std;

int main()
{
	// float �� ������ �����Ҵ� �ް�
	float* myFloat = new float(3.14f);
	cout << "myFloat �ּ�: " << &myFloat << '\n';
	cout << "myFloat ��: " << *myFloat << '\n';
	delete myFloat;
	

	float* c_array = (float*)malloc(20);
	for (int i = 0; i < 5; ++i)
	{
		// *(c_array + i) = i + 0.1f;
		c_array[i] = i + 0.1f;		// NULL �� �ʱ�ȭ�� �Ͱ� ���Ƽ� ��� ��
		printf("c_array[%i] = %.1f \n", i, c_array[i]);
	}

	free(c_array);
	c_array = NULL;


	cout << '\n';
	float* cpp_array = new float[5]{ 0.4f, 1.4f, 2.4f, 3.4f, 4.4f };
	for (int i = 0; i < 5; ++i)
	{
		// *(c_array + i) = i + 0.1f;
		// cpp_array[i] = i + 0.1f;
		printf("c_array[%i] = %.1f \n", i, cpp_array[i]);
	}
	delete[] cpp_array;		// �����Ҵ��� �迭�� ������ �� delete[] ����ؾ� �մϴ�.
	cpp_array = nullptr;

	return 0;
}
