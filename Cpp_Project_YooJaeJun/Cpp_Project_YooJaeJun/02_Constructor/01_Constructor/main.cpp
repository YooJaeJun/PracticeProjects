#include <Windows.h>
#include "SampleClass.h"

#define LINE cout<<endl

int main()
{
	printf("SampleClass sampleClass 로 선언 \n");
	// 호출할 생성자를 명시하지 않는다면 매개변수가 없는 생성자가 호출됩니다.
	SampleClass sampleClass1;
	LINE;

	// 접근자를 통해 private 로 설정되어 있는 멤버의 값을 가져옵니다.
	printf("처음 설정된 값 \n");
	printf("[A : %i] [B : %i] \n", sampleClass1.GetA(), sampleClass1.GetB());
	LINE;

	printf("CreateInit Call! \n");
	sampleClass1.CreateInit();
	sampleClass1.Print();
	LINE;

	printf("SetMember Call! \n");
	sampleClass1.SetMember(30, 40);
	sampleClass1.Print();
	LINE;


	system("pause");
	system("cls");

	// 오버로딩된 생성자를 선택하여 호출 하는 방법
	// "클래스명" "객체이름" = 사용할 생성자(매개변수목록);
	printf("SampleClass sampleClass = SamepleClass() 로 선언 \n");
	SampleClass sampleClass2 = SampleClass();
	sampleClass2.Print();

	system("pause");
	system("cls");

	printf("SampleClass sampleClass = SamepleClass(20, 30) 로 선언 \n");
	SampleClass sampleClass3 = SampleClass(20, 30);
	sampleClass3.Print();

	system("pause");
	system("cls");

	// "= 생성자(매개변수목록)" 을 생략하고
	// 객체이름(매개변수목록) 으로도 사용할 생성자를 지정할 수 있습니다.
	printf("SampleClass sampleClass(50, 50) 로 선언 \n");
	SampleClass sampleClass4(50, 50);
	sampleClass4.Print();

	// 매개변수가 없는 생성자는 위의 형식을 사용할 수 없습니다.
	// SampleClass sampleClass5();


	// 기본 생성자 (Default Constructor) 에 대해서 조사해오세요.
	// 의미, 사용처 등

	return 0;
}