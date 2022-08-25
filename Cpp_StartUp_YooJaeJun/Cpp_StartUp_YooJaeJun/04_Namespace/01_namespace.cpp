#include <iostream>

// 네임 스페이스 (namespace)
// 코드블록에 이름을 붙여주는 기능을 의미합니다.
// 해당 네임스페이스 공간의 요소에 접근할 때 :: (스코프 연산자)를 사용합니다.

// :: (범위접근연산자, 스코프 연산자): 이름이 존재하는 코드블럭 에 접근하는 연산자입니다.

namespace namespace_1
{
	int a = 10;
	int b = 20;
}
namespace namespace_2
{
	int a = 20;
}

// 특정 네임스페이스에 대한 접근을 지정할 때 using 을 사용합니다.
using namespace namespace_2;
using namespace std;

extern int g_var;
// extern static int g_staticVar;	
// extern int g_staticVar;

// extern int var_1;	// 익명 네임스페이스 안에 선언한 전역변수이므로 다른 파일에서 접근 불가

int main()
{
	cout << "namespace_1::A : " << namespace_1::a << endl;
	cout << "namespace_2::A : " << namespace_2::a << endl;
	cout << "namespace_2::A : " << a << endl;
	// using 또한 namespace 이므로 using 을 사용하여 생략이 가능합니다.

	cout << "g_var : " << g_var << endl;
	// cout << "g_staticVar : " << g_staticVar << endl;	// static 변수 다른 파일에서 접근 불가
	
	// cout << "var_1 : " << var_1 << endl;	// 익명 네임스페이스 안에 선언한 전역변수이므로 다른 파일에서 접근 불가

	return 0;
}
