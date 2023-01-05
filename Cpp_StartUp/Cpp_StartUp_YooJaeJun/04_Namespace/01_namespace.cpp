#include <iostream>

// ���� �����̽� (namespace)
// �ڵ��Ͽ� �̸��� �ٿ��ִ� ����� �ǹ��մϴ�.
// �ش� ���ӽ����̽� ������ ��ҿ� ������ �� :: (������ ������)�� ����մϴ�.

// :: (�������ٿ�����, ������ ������): �̸��� �����ϴ� �ڵ�� �� �����ϴ� �������Դϴ�.

namespace namespace_1
{
	int a = 10;
	int b = 20;
}
namespace namespace_2
{
	int a = 20;
}

// Ư�� ���ӽ����̽��� ���� ������ ������ �� using �� ����մϴ�.
using namespace namespace_2;
using namespace std;

extern int g_var;
// extern static int g_staticVar;	
// extern int g_staticVar;

// extern int var_1;	// �͸� ���ӽ����̽� �ȿ� ������ ���������̹Ƿ� �ٸ� ���Ͽ��� ���� �Ұ�

int main()
{
	cout << "namespace_1::A : " << namespace_1::a << endl;
	cout << "namespace_2::A : " << namespace_2::a << endl;
	cout << "namespace_2::A : " << a << endl;
	// using ���� namespace �̹Ƿ� using �� ����Ͽ� ������ �����մϴ�.

	cout << "g_var : " << g_var << endl;
	// cout << "g_staticVar : " << g_staticVar << endl;	// static ���� �ٸ� ���Ͽ��� ���� �Ұ�
	
	// cout << "var_1 : " << var_1 << endl;	// �͸� ���ӽ����̽� �ȿ� ������ ���������̹Ƿ� �ٸ� ���Ͽ��� ���� �Ұ�

	return 0;
}
