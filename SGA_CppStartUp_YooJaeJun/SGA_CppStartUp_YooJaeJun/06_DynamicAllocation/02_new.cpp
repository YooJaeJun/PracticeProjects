#include <iostream>
using namespace std;

int main()
{
	// float 형 공간을 동적할당 받고
	float* myFloat = new float(3.14f);
	cout << "myFloat 주소: " << &myFloat << '\n';
	cout << "myFloat 값: " << *myFloat << '\n';
	delete myFloat;
	

	float* c_array = (float*)malloc(20);
	for (int i = 0; i < 5; ++i)
	{
		// *(c_array + i) = i + 0.1f;
		c_array[i] = i + 0.1f;		// NULL 로 초기화된 것과 같아서 경고 뜸
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
	delete[] cpp_array;		// 동적할당한 배열을 해제할 시 delete[] 사용해야 합니다.
	cpp_array = nullptr;

	return 0;
}
