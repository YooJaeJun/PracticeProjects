#include <stdio.h>
#include <Windows.h>

void simulation();
void addition(int, int);	// ���� �ÿ��� �ڷ����� �����ص� �۵�
void subtraction(int, int);
void multiplication(int num1, int num2);
void division(int num1, int num2);
void remained(int num1, int num2);
float getDamage();
int buy(int);

int main()
{
	// for (int i = 0; i<5; ++i)
	// simulation();

	// addition(10, 20);
	// subtraction(10, 20);
	// multiplication(10, 20);
	// division(10, 20);
	// remained(10, 20);

	// 1 + 1;
	// int damage = getDamage();
	// printf("��ȯ�� Damage : %.2lf \n", getDamage());

	int money;
	printf("�������� �Է����ּ��� : ");
	scanf_s("%i", &money);
	
	while (money > 1000)
	{
		printf("���� ������ : %i \n", money);
		money = buy(money);
	}

	return 0;
}


// cdcel : �Լ��̸�(�Ű�����) : ���� �ۼ�
// stdcall : main : ��ǻ�Ͱ� ȣ��
