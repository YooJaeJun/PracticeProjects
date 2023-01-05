#include <iostream>
using namespace std;

// ���ø� Ŭ����
template<typename T, typename U>
class TemplateClass
{
private:
	T Num1;
	U Num2;

public:
	TemplateClass() 
	{ 
		Num1 = 0;
		Num2 = 0;
	}
	TemplateClass(T num1, U num2)
	{ 
		Num1 = num1;
		Num2 = num2;
	}
	
	void Print() const
	{
		cout << Num1 << " : " << Num2 << endl;
	}

	T Add(const T num1, const T num2)
	{
		return num1 + num2;
	}
	
	// Ŭ���� �ȿ� ���ø� �Լ��� �����մϴ�.
	// �ش� ������ Ŭ������ ������ �� Ŭ������ T ��������
	// ��ȯ���� �ʽ��ϴ�.
	template<typename T>
	T Sub(const T num1, const T num2)
	{
		return num1 - num2;
	}
};

int main()
{
	TemplateClass<int, float> sample1(10, 20.14f);
	sample1.Print();

	cout << sample1.Add(30, 40) << endl;
	cout << sample1.Sub<double>(1.5, 0.5) << endl;
	cout << sample1.Sub<int>(30, 10) << endl;
	// cout << sample1.Sub() << endl;
	// cout << sample1.Add() << endl;

	return 0;
}


// ...
// ���ø� Ŭ������ ����� ���Ǳ��� �ۼ�
// ��� ���Ͽ� ���� �ۼ� �� �ϴ� �� ������ ���߿� ���
