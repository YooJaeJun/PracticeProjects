#include <iostream>
using namespace std;

// 템플릿 클래스
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
	
	// 클래스 안에 템플릿 함수를 선언합니다.
	// 해당 형식은 클래스를 선언할 때 클래스의 T 형식으로
	// 전환되지 않습니다.
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
// 템플릿 클래스는 헤더에 정의까지 작성
// 헤더 파일에 정의 작성 안 하는 법 있지만 나중에 배움
