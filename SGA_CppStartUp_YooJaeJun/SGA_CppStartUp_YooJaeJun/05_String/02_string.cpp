#include <iostream>
#include <string>
using namespace std;

int main()
{
	string weapon;
	string atk = "���ݷ� : ";
	
	// 1. weapon �� ����� �Է¹޾� �������ּ���.
	// 2. atk �� int ������ �Է¹��� �� �ش� ���� atk �� �̾��ּ���.

	// ex)
	// ������ �̸��� �Է��ϼ��� : �Ѽ� ��
	// ������ ���ݷ��� �Է��ϼ��� : 22

	cout << "������ �̸��� �Է��ϼ��� : ";
	getline(cin, weapon);
	cout << "������ ���ݷ��� �Է��ϼ��� : ";
	int atkInt;
	cin >> atkInt;
	atk += to_string(atkInt);
	cout << weapon << '\n' << atk;

	return 0;
}