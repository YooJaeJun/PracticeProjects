#include <iostream>
// #include <combaseapi.h>
#include <Windows.h>
using namespace std;

class NotInstance1
{
private:
	NotInstance1() = default;
	virtual ~NotInstance1() = default;

};

class NotInstance2
{
protected:
	NotInstance2() = default;
	virtual ~NotInstance2() = default;
};

class Abstract1
{
public:
	Abstract1() = default;
	virtual ~Abstract1() = default;

	void NoExpression();	// �Լ��� ���Ǹ� �����ϰ� ���� �մϴ�.
};

class Abstract2 abstract	// �ش� Ŭ������ �߻� Ŭ������ ����ϴ�.
{
public:
	Abstract2() = default;
	virtual ~Abstract2() = default;

	// ���� ���� �Լ��� �����մϴ�.
	// = 0; PURE; abstract; �� �ۼ��Ͽ� ������ �� �ֽ��ϴ�.
	// PURE �� ���� ��� comaseapi �� Windows.h �� ���Խ��Ѿ� �մϴ�.
	// ���ǰ� ���� �Լ��Դϴ�.
	// �Ļ� Ŭ�������� �ݵ�� �������� ���� ����մϴ�.
	// ���������Լ��� �����ϰ� �ִ� Ŭ������
	// �ҿ����� Ŭ���� �� �߻� Ŭ������� �մϴ�.
	// �߻� Ŭ���� ������ �ܺο��� ����� �� �����ϴ�.
	virtual void PureFunc1() = 0;
	virtual void PureFunc2() PURE;
	virtual void PureFunc3() abstract;
};

/*
class SampleClass1 : public NotInstance1
{
public:
	SampleClass1() = default;
};
class SampleClass2 : public NotInstance2
{
public:
	SampleClass2() = default;
};
*/
class SampleClass3 : public Abstract1
{
public:
	SampleClass3() = default;

	// Abstract1 �� ���ǵ��� ���� �Լ��� �Ļ� Ŭ�������� �������մϴ�.
	void NoExpression()
	{
		cout << "NoExpression Override " << '\n';
	}
};
class SampleClass4 : public Abstract2	// ctrl + . �� ���� ���� �Լ� ����
{
public:
	SampleClass4() = default;
	

	// Abstract2��(��) ���� ��ӵ�
	virtual void PureFunc1() override
	{
		cout << "PureFunc1" << endl;
	}

	virtual void PureFunc2() override
	{
		cout << "PureFunc2" << endl;
	}

	virtual void PureFunc3() override
	{
		cout << "PureFunc3" << endl;
	}
};

class Abstract abstract // final
{
// private:
protected:
	Abstract() = default;

// private:
public:
	// virtual void A() abstract;	// final;
	virtual const int* const& A() const abstract;
};
class B : public Abstract
{
	// Abstract��(��) ���� ��ӵ�
	/*__forceinline*/ virtual const int* const& A() const override final
	{

	}
}


int main()
{
	// �����ڰ� private �̹Ƿ� �ܺο��� �����ڸ� ȣ���� �� ���� ���� �Ұ�
	// NotInstance1 not1;	
	// �����ڰ� protected �̹Ƿ� �ܺο��� �����ڸ� ȣ���� �� ���� ���� �Ұ� 
	// NotInstance2 not2;	

	// ��� Ŭ������ �����ڰ� private �̹Ƿ�
	// �Ļ� Ŭ������ �����ڸ� ȣ���� �� ��� Ŭ������ �����ڿ� ������ �� ���� ������ �Ұ����մϴ�.
	// SampleClass1 sample1 = SampleClass1();
	
	// ��� Ŭ������ �����ڰ� protected �̹Ƿ�
	// �Ļ� Ŭ������ �����ڸ� ���ؼ��� ��� Ŭ������ �����ڸ� ȣ���� �� �ֽ��ϴ�.
	// SampleClass2 sample2 = SampleClass2();
	// ���� ���� ���ǵ��� ���� �Լ��� ������ �ִ� Ŭ������ �ش� Ŭ������
	// ��� ����	Ŭ������ ������� �ʴ� ���� �����ϴ�. 


	Abstract1 abstract1;
	// �Լ��� ���ǰ� ���� �Լ��� ȣ���ϰ� �����Ƿ� Error �� ���ϴ�.
	// abstract1.NoExpression();

	SampleClass3 sample3 = SampleClass3();
	// ��� Ŭ�������� ���ǵ��� ���� �Լ��� �Ļ� Ŭ�������� �������Ͽ�
	// �Լ��� ȣ���մϴ�.
	// sample3.NoExpression();


	// �߻� Ŭ�����̹Ƿ� �ܺο��� ���� �Ұ�
	// Abstract2 abstract2;
	// �߻� Ŭ������ ���� ���� �Լ��� ��� �����߱� ������ ���� ����
	SampleClass4 sample4 = SampleClass4();
	sample4.PureFunc1();
	sample4.PureFunc2();
	sample4.PureFunc3();


	// ��ü ���� 5�� ��Ģ
	// SOLID
	// Single Responsibility Principle ���� å�� ��Ģ

	
	// ��ü ������ 4�� �Ӽ�
	// ĸ��ȭ 
	//		Ư�� ��ü�� ���������� ���� ����� �����ϱ� ���� �ʿ��� �����Ϳ� ����� �ϳ��� ���� ��(���ȭ)
	//		������ ��ü �ȿ� ���Խ�Ű��, �� ������ ���� ���� ������ ������� �ʴ� ���,
	//		�ʿ信 ���� Ȯ���� �������̽��� �ܺο� �����ϴ� ���
	//		��ü�� ������ �������̸� ���α׷��� ��ǰ���� Ȱ��ȴ�.
	//		Ű����: '���´�'
	// ��Ӽ�
	//		���� ������ Ư¡�� ���� ������ �����޴� ��
	//		���� Ŭ������ ���� Ŭ������ Ư���� �����ϰ�, Ȯ���Ѵ�.
	//		���� ��ü�� �ִ��� ��Ȱ���ϸ� ��ӹ޾� ���ϴ� �κи� �����Ͽ� �ð��� ����� �����Ѵ�.
	//		Ű����: '�����Ѵ�'
	// �߻�ȭ 
	//		��ü���� �������� Ư¡�� �̾� �̸��� ���̴� ��
	//		��ü���� ���� �����ؼ� ���� ������ �ִ� Ư���� ������ ������ �Ѵ�. (= ������ �𵨸�)
	//		�𵨸��� ���, �ʿ��� �ڷ�� ������ ����� �ۼ��Ǹ� ��ü�� �����ϴ� ��
	//		Ű����: 'ǥ���Ѵ�'
	// ������
	//		�Ȱ��� ȣ���̶� ��Ȳ�� ����, ȣ���ϴ� ��ü�� ���� �ٸ� ������ �� �� �ִ� �ɷ�
	//		���� ���� ������ �ٸ����� ���������� ������ ������ �ϴ� �Լ��� �ϳ��� �������̽��� ȣ��
	//		�������� ��Ÿ�ӿ� ���� ���ε��� �ϴ� ���� �Լ��� ���� �����ȴ�.
	//		Ű����: '��Ȳ�� ���� �޶�����'



	// �Ϲ�ȭ ���α׷���

	return 0;
}
