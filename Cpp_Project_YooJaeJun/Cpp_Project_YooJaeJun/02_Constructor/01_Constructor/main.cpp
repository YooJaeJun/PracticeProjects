#include <Windows.h>
#include "SampleClass.h"

#define LINE cout<<endl

int main()
{
	printf("SampleClass sampleClass �� ���� \n");
	// ȣ���� �����ڸ� ������� �ʴ´ٸ� �Ű������� ���� �����ڰ� ȣ��˴ϴ�.
	SampleClass sampleClass1;
	LINE;

	// �����ڸ� ���� private �� �����Ǿ� �ִ� ����� ���� �����ɴϴ�.
	printf("ó�� ������ �� \n");
	printf("[A : %i] [B : %i] \n", sampleClass1.GetA(), sampleClass1.GetB());
	LINE;

	printf("CreateInit Call! \n");
	sampleClass1.CreateInit();
	sampleClass1.Print();
	LINE;

	printf("SetMember Call! \n");
	sampleClass1.SetMember(30, 40);
	sampleClass1.Print();
	LINE;


	system("pause");
	system("cls");

	// �����ε��� �����ڸ� �����Ͽ� ȣ�� �ϴ� ���
	// "Ŭ������" "��ü�̸�" = ����� ������(�Ű��������);
	printf("SampleClass sampleClass = SamepleClass() �� ���� \n");
	SampleClass sampleClass2 = SampleClass();
	sampleClass2.Print();

	system("pause");
	system("cls");

	printf("SampleClass sampleClass = SamepleClass(20, 30) �� ���� \n");
	SampleClass sampleClass3 = SampleClass(20, 30);
	sampleClass3.Print();

	system("pause");
	system("cls");

	// "= ������(�Ű��������)" �� �����ϰ�
	// ��ü�̸�(�Ű��������) ���ε� ����� �����ڸ� ������ �� �ֽ��ϴ�.
	printf("SampleClass sampleClass(50, 50) �� ���� \n");
	SampleClass sampleClass4(50, 50);
	sampleClass4.Print();

	// �Ű������� ���� �����ڴ� ���� ������ ����� �� �����ϴ�.
	// SampleClass sampleClass5();


	// �⺻ ������ (Default Constructor) �� ���ؼ� �����ؿ�����.
	// 
	// �ǹ�: Ŭ���� ��ü ���� �� ������ ���ÿ� �����Ϸ��� �⺻������ �����ϴ� ������
	// 
	// ����: ��ü�� ������� �Ϲݺ����� ���� ��Ģ�� �⺻������ �ʱ�ȭ�Ѵ�.
	//		�⺻���̶�?
	//			����, ���� ��ü: ��� ����� 0���� �ʱ�ȭ
	//			���� ��ü: �ʱ�ȭ���� �ʴ� �����Ⱚ�� ������.
	// 
	// ����: Ŭ�����̸�() {};		
	//		Ŭ������ �̸��� ������, ��� �Ű������� ���޹��� �ʴ´�.
	// 
	// Ư¡: �����ڰ� �ϳ��� ����� Ŭ������ �⺻ �����ڸ� ȣ������ �ʴ´�.
	// 
	// ����: ���α׷��Ӱ� �Ű������� �ִ� �����ڵ鸸 �����ߴٸ�, 
	//		�Ű����� ���� Ŭ���� ��ü ���� �� �⺻ �����ڰ� ���� ������ ��´�.

	return 0;
}