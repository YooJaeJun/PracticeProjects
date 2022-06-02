#include <iostream>
using namespace std;

// This Pointer
// 자기 자신을 가리키는 포인터로 구조체와 클래스에서만 사용할 수 있는 포인터입니다.
// 객체 자신의 위치를 반환합니다.

class Sample
{
private:
	int A = 0;
	int B = 0;

public:
	Sample() = default;

	Sample(int A, int B)
	{
		this->A = A;
		this->B = B;
		cout << "this : " << this << endl;
	}

	__forceinline void Print() const
	{
		cout << A << " : " << B << endl;
	}

	void Destroy()
	{
		// 자기 자신의 할당을 해제합니다.
		// delete 같은 경우 동적할당한 공간을 해제하기 때문에 
		// 동적할당으로 생성하지 않은 경우 오류가 나타납니다.
		delete this;
	}

	~Sample()
	{
		cout << "Finallizer Call" << endl;
	}
};

int main()
{
	Sample* p_sample = new Sample();
	p_sample->Destroy();


	Sample sample_1(10, 20);
	cout << "sample_1 Address : " << &sample_1 << endl;
	sample_1.Print();
	// sample_1.Destroy();

	// Sample* p_sample = &sample_1;
	// p_sample->Print();
	
	Sample sample_2(30, 20);
	cout << "sample_1 Address : " << &sample_2 << endl;
	sample_2.Print();


	return 0;
}