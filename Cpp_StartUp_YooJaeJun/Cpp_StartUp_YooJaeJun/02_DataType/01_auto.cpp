#include <iostream>

// auto (Ÿ���߷���)
// ������ Ÿ�ӿ� �ڷ����� �����Ǵ� Ÿ���Դϴ�.
// �ڷ����� �߷��ؾ� �ϱ� ������ �ݵ�� ����� ���ÿ� �ʱ�ȭ�� �����ؾ� �մϴ�.

int main()
{
	auto myInt = 10;
	auto myFloat = 3.14f;
	auto myDouble = 3.14;
	auto myChar = 'A';

	std::cout << "[myInt]   ::" << "[Size : " << sizeof(myInt) << "]::[Value : " << myInt << "]" << '\n';
	std::cout << "[myFloat] ::" << "[Size : " << sizeof(myFloat) << "]::[Value : " << myFloat << "]" << '\n';
	std::cout << "[myDouble]::" << "[Size : " << sizeof(myDouble) << "]::[Value : " << myDouble << "]" << '\n';
	std::cout << "[myChar]  ::" << "[Size : " << sizeof(myChar) << "]::[Value : " << myChar << "]" << '\n';


	return 0;
}