#include "SampleClass.h"

// .h 파일에 선언되어 있는 함수를 .cpp 에서 정의하는 방법
// 반환형 클래스이름::멤버함수이름(매개변수 목록)
void SampleClass::Print()
{
	cout << "A : " << A << endl;
}