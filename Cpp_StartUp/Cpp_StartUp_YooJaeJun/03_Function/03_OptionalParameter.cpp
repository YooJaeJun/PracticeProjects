#include <iostream>

// ������ �Ű����� (Optional Prameter)
// Cpp �������ʹ� �Ű������� �⺻���� �� �� �ִ� ������ �Ű������� �����մϴ�.
// ������ �Ű������� �ʿ信 ���� �Լ� ȣ�� �� ������ �����ϸ�
// ������ �ÿ� ������ �⺻���� ���ϴ�.
// �ݵ�� �ʼ� �Ű����� (�Լ� ȣ�� �� �ݵ�� �ۼ��ؾ��ϴ�) �Ű����� �ڿ� �ۼ��ϼž� �մϴ�.
// ������ �Ű������� �� ���� �ƴ� ���� ���� ��� �����մϴ�.

//							sizePrint �� false ��� �⺻���� �ۼ��� ������ �Ű������� ����ϴ�.
void checkInt(int integer = 1, bool sizePrint = false)
{
	if (sizePrint)
		std::cout << "integer Size : " << sizeof(integer) << '\n';
	
	std::cout << "inter Value  : " << integer << '\n';
}

// void Print(int num1, int num2 = 0, int num3)	// ������ ���� ������ �Ұ���
void Print(int num1, int num2 = 0, int num3 = 0)
{
	printf("num1 : %i \n", num1);
	if (num2)
		printf("num2 : %i \n", num2);
	if (num3)
		printf("num3 : %i \n", num3);
}

// ������ �Ű������θ� �Ű����� ����� ä�� ���� �ֽ��ϴ�.
void optionalParameter(bool boolean = false)
{
	printf("boolean : %s \n", (boolean ? "True" : "False"));
}

int main()
{
	checkInt(10, true);
	checkInt(20, false);
	checkInt(20);
	checkInt();

	Print(10);
	Print(10, 20);
	Print(10, 20, 30);

	optionalParameter(true);
	optionalParameter();


	return 0;
}
