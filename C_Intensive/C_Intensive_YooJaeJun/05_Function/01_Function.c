#include <stdio.h>

// �Լ� ������
// �Լ��� �̸��� �Լ��� �����ϰ� �ִ� �޸� �ּҰ��Դϴ�.
// �̷��� �Լ��� �����ϴ� �ּҸ� �����ϰ� �ִ� �����͸� �ǹ��մϴ�.

void Hello()
{
	printf("Hello \n");
}
void Hello_2()
{
	printf("Hello_2 \n");
}

double Mul(int a, double b)
{
	return a * b;
}

int main()
{
	printf("Hello �Լ��� �����ϰ� �ִ� �ּ� : %p \n", Hello);	// �ڵ� �����
	Hello();
	// () : �Լ� ȣ�� ������
	//		�Լ� �̸� �ڿ� ����ϸ� �ش� �ּҰ��� �ִ� �Լ��� �������ִ� �������Դϴ�.

	// ��ȯ���� �Ű������� �ڷ����� ����ų �Լ��� ��ȯ���� �Ű������� �ڷ�����
	// �ۼ��Ͻø� �˴ϴ�.
	// ��ȯ��(*�Լ��������̸�)(�Ű������� �ڷ���)
	void(*pHello)() = Hello;
	printf("pHello�� �����ϰ� �ִ� �ּ� : %p \n", pHello);
	pHello();

	unsigned long long size = (unsigned long long)&Hello_2 - (unsigned long long)&Hello;

	printf("%lld \n", size);

	double(*pMul)(int, double) = Mul;

	printf("10 * 0.5 = %.2lf \n", pMul(10, 0.5));

	return 0;
}