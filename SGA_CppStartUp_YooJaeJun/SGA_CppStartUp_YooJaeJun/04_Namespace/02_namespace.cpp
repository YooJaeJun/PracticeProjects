// 전역 변수
// 모든 파일이나 공간에서 접근이 가능한 변수입니다.
// extern 키워드를 이용하여 다른 파일에서도 사용이 가능합니다.
int g_var = 10;

// 정적 전역 변수
// 선언되어 있는 파일 안의 공간에서 어디서나 접근이 가능합니다.
// 다른 파일에서는 접근이 불가능한 변수입니다.
static int g_staticVar = 20;

// static int var_1 = 20;
// static int var_2 = 20;
// static int var_3 = 20;
// static int var_4 = 20;
// static int var_5 = 20;

// 익명 네임스페이스
// 이름이 없는 네임스페이스로 해당 공간에 선언한 모든 요소는
// static 키워드가 붙는 요소로 사용할 수 있습니다.
namespace
{
	int var_1 = 20;
	int var_2 = 20;
	int var_3 = 20;
	int var_4 = 20;
	int var_5 = 20;
}
