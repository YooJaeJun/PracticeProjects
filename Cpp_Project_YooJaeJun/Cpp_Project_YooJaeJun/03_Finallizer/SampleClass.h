#pragma once
#include <iostream>
using namespace std;

class SampleClass
{
private:
	string Name;

public:
	SampleClass(string name);

	// �Ҹ���
	// ��ü�� �Ҹ��� �� ȣ��Ǹ�
	// ~Ŭ�����̸�() ���� �����մϴ�.
	// �Ű������� ����� �Ұ����ϱ� ������ �����ε��� �Ұ����մϴ�.
	// ��ü �Ҹ��� �� �ݵ�� ȣ��Ǿ�� �մϴ�.
	// �Ҹ��ڸ� �������� �ʴ´ٸ� �����Ϸ����� �⺻ �Ҹ��ڸ� �����մϴ�.
	// �Ҹ��ڸ� �����Ѵٸ� �����Ϸ����� �⺻ �Ҹ��ڸ� �������� �ʽ��ϴ�.
	// �⺻ �Ҹ���
	// ~SampleCalss() = default;
	// ~SampleClass() {};
	~SampleClass();
	
};

