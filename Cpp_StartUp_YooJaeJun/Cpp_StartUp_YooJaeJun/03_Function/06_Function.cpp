#include <iostream>

// void test(auto a) {} auto �ڷ����� �Ķ������ Ÿ������ ������ �Ұ����մϴ�.

// auto �� ��ȯ�����δ� ����� �����մϴ�.
// ��ȯ���� �� �̻� ����� �Ұ����մϴ�.
auto test()
{
	char      a = 0;
	short     b = 0;
	int       c = 0;
	long long d = 0;

	// if (true) return b;	- ��ȯ ������ auto �̹Ƿ� return �� �� �� �̻� ��� �Ұ� -

	return a;
}


int main()
{
	std::cout << sizeof(test());

	return 0;
}