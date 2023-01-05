#include "struct/SampleStruct.h"
// ���� ���赵�� ����ϱ� ���� ���赵�� ����Ǿ� �ִ�
// .h �� ���Խ�ŵ�ϴ�.
// Folder/ : �ش� ������ ��η� �̵��մϴ�.
#include "class/SampleClass.h"

int main()
{
	// ����ü ������ ��ü�� �����մϴ�.
	SampleStruct myStruct;
	myStruct.Public = 20;		// struct ���� �������ڸ� ������� ���� ����̹Ƿ� 
								// public ���� ������ �Ǿ��� ������ �ܺο��� ���� ����
	// myStruct.A = 10;
	// myStruct.Print();		// private �� ����Ǿ��� ������ �ܺο��� ���� �Ұ���
	myStruct.B = 20;			// public ���� ����Ǿ��� ������ �ܺο��� ���� ����

	// Ŭ���� ������ ��ü�� �����մϴ�.
	SampleClass myClass;
	// myClass.Private = 20;	// class ���� ���������ڸ� ������� ���� ����̹Ƿ�
								// private �� ������ �Ǿ��� ������ �ܺο��� ���� �Ұ���
	myClass.A = 20;
	myClass.Print();			// public ���� ����Ǿ��� ������ �ܺο��� ���� ����
	// myClass.B = 20;			// private �� ����Ǿ��� ������ �ܺο��� ���� �Ұ���
								

	return 0;
}