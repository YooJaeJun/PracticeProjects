#include <stdio.h>

// ���� ������
// �������� �ּҰ��� ����Ű�� �����͸� �ǹ��մϴ�.

int main()
{
	int var = 10;
	int* p = &var;
	// ���������� ������
	// ����ų �����Ϳ��� * �� �ϳ� �߰��Ͽ� �����մϴ�.
	int** pp = &p;	// int* ������ �ּҰ��� ����ų pp �� �����մϴ�.
	int*** ppp = &pp;	// int** ������ �ּҰ��� ����ų ppp�� �����մϴ�.

	printf("var    : %i \n", var);
	printf("*p     : %i \n", *p);
	printf("**pp   : %i \n", **pp);
	printf("***ppp : %i \n", ***ppp);
	printf("---------------------------\n");
	printf("&var   : %p \n", &var);
	printf("p      : %p \n", p);
	printf("*pp    : %p \n", *pp);
	printf("**ppp  : %p \n", **ppp);
	printf("---------------------------\n");
	printf("&p     : %p \n", &p);
	printf("pp     : %p \n", pp);
	printf("*ppp   : %p \n", *ppp);
	printf("---------------------------\n");
	printf("&pp    : %p \n", &pp);
	printf("ppp    : %p \n", ppp);
	printf("---------------------------\n");
	printf("&ppp   : %p \n", &ppp);

	// ppp == pp �� �ּҰ�
	// *ppp == pp �� �ּҰ��� ����ִ� �� == p �� �ּҰ�
	// **ppp == p �� �ּҰ��� ����ִ� �� == var �� �ּҰ�
	// ***ppp == var �� �ּҰ��� ����ִ� �� == var �� ������ �ִ� ��

	return 0;
}