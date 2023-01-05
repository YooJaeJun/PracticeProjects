#include <iostream>

// C
/*
typedef struct tag_myStruct
{
	int a;
	int b;
	int c;

}myStruct;
*/

// Cpp
// typedef �� ������� �ʰ� ����ü ������ ������ �����մϴ�.
struct myStruct
{
	// ��� ������ �⺻���� �־��� �� �ֽ��ϴ�.
	int a = 10;
	int b = 20;
	int c = 30;

	// ��� �Լ��� �߰��˴ϴ�.
	// ��ü : ���赵�� �������� ������� ������Ʈ
	void print()	// ȣ���ϴ� ��ü�� �������� ����� �����մϴ�.
	{
		printf("a : %i \n", a);
		printf("b : %i \n", b);
		printf("c : %i \n", c);
	}
};

int main()
{
	myStruct myStruct_1;
	printf("myStruct_1.a : %i \n", myStruct_1.a);
	printf("myStruct_1.b : %i \n", myStruct_1.b);
	printf("myStruct_1.c : %i \n", myStruct_1.c);
	std::cout << '\n';

	printf("myStruct_1 �� ��� ��� \n");
	myStruct_1.print();
	std::cout << '\n';

	myStruct myStruct_2;
	myStruct_2.a = 100;
	printf("myStruct_2 �� ��� ��� \n");
	myStruct_2.print();
	std::cout << '\n';

	/*
	
	C (���� ������ ���)
	- �Լ� ������ ���
	- �������� �ܼ���
	- ������ �ڵ带 �ۼ��ϱ� ���� ����
	- �ӵ��� �ſ� ���� ���� Ư¡
	- ���� ���迡 �ð��� ���� ���.
	
	CPP (��ü ������ ���)
	- ��ü
	- �������� ������
	- ������ �ڵ带 �ۼ��ϱ� �˸���
	- ���� ���谡 �ſ� �����
	- �ӵ��� �����ϴ�.

	��ü: ���赵�� �������� ������� ������Ʈ
	- ���赵: class, struct
	- ������Ʈ: ����
	- ���� ���赵�� ������� ��ü���� �ڱ� �ڽŸ��� ���� ����
	- �ٸ� ��ü�� ����Ǵ��� ���� ������� �ʴ� ���� Ư¡�Դϴ�.

	*/

	return 0;
}
