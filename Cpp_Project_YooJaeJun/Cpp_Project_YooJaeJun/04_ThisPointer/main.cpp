#include <iostream>
using namespace std;

// This Pointer
// �ڱ� �ڽ��� ����Ű�� �����ͷ� ����ü�� Ŭ���������� ����� �� �ִ� �������Դϴ�.
// ��ü �ڽ��� ��ġ�� ��ȯ�մϴ�.

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
		// �ڱ� �ڽ��� �Ҵ��� �����մϴ�.
		// delete ���� ��� �����Ҵ��� ������ �����ϱ� ������ 
		// �����Ҵ����� �������� ���� ��� ������ ��Ÿ���ϴ�.
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