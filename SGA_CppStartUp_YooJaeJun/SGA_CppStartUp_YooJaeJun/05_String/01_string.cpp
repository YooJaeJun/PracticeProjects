#include <iostream>
#include <string>
// C++ ���� �����ϴ� ���ڿ� ���� ���̺귯�� �Դϴ�. (C �� ��� <string.h>)  <== �ƴ�. c++���� �����Ǵ� �� cstring ��.
using namespace std;
#pragma warning (disable : 4996)

// string
// C++ �������� �����ϴ� ���ڿ� ���� �ڷᱸ���Դϴ�.

int main()
{
	string str_1 = "Hello World!";
	cout << str_1 << endl;			// cout ���·� ����� ��
	printf("%s \n", str_1.c_str());	// printf ���·� ����� ��

	string str_2 = "Hello";
	string str_3 = str_2 + " World!";
	// ���ڿ������� ������ �����մϴ�.
	printf("%s \n", str_3.c_str());
	
	// printf("str_3 ���� : %zi \n", strlen(str_3.c_str()));
	// length() : �ι��ڸ� ������ ���ڿ��� ���̸� ��ȯ�մϴ�.
	printf("str_3 ���� : %zi \n", str_3.length());

	// �񱳿��� ���� �����մϴ�.
	if (str_1 == str_3) printf("str_1 �� str_2 �� ���ڿ��� �����ϴ�. \n");

	
	char inputChar[100];
	string inputString;
	cout << "���ڿ��� �Է��ϼ��� \n";
	cin.getline(inputChar, sizeof(inputChar));
	printf("�Է¹��� ���ڿ� : %s \n", inputChar);

	cout << "���ڿ��� �Է��ϼ��� \n";
	getline(cin, inputString);
	printf("�Է¹��� ���ڿ� : %s \n", inputString.c_str());
	
	// to_string(value) : ������, �Ǽ��� �����͸� ���ڿ� �����ͷ� �����մϴ�.
	inputString = to_string(100);
	printf("���ڿ� ���� : %s \n", inputString.c_str());

	inputString = to_string(3.14);
	float myFloat = stof(inputString);
	printf("�Ǽ��� ���� : %.2f \n", myFloat);
	// stoi : string �� int �� ����
	// stod : string �� double �� ����
	// stoll : string �� long long ���� ����

	


	// ������ ������
	cout << fixed;	// �Ҽ��� ����
	cout.precision(5);	// �ڸ��� ���� ǥ��
	cout << inputString << endl;
	cout.unsetf(ios::fixed);	// ���� cout �� ����� �κ� ����

	return 0;
}