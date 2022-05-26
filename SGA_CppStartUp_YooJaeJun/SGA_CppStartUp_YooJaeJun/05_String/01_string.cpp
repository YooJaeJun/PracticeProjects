#include <iostream>
#include <string>
// C++ 에서 제공하는 문자열 관련 라이브러리 입니다. (C 의 경우 <string.h>)  <== 아님. c++에서 대응되는 건 cstring 임.
using namespace std;
#pragma warning (disable : 4996)

// string
// C++ 에서부터 제공하는 문자열 관련 자료구조입니다.

int main()
{
	string str_1 = "Hello World!";
	cout << str_1 << endl;			// cout 형태로 출력할 시
	printf("%s \n", str_1.c_str());	// printf 형태로 출력할 시

	string str_2 = "Hello";
	string str_3 = str_2 + " World!";
	// 문자열끼리의 덧셈이 가능합니다.
	printf("%s \n", str_3.c_str());
	
	// printf("str_3 길이 : %zi \n", strlen(str_3.c_str()));
	// length() : 널문자를 제외한 문자열의 길이를 반환합니다.
	printf("str_3 길이 : %zi \n", str_3.length());

	// 비교연산 또한 가능합니다.
	if (str_1 == str_3) printf("str_1 과 str_2 의 문자열은 같습니다. \n");

	
	char inputChar[100];
	string inputString;
	cout << "문자열을 입력하세요 \n";
	cin.getline(inputChar, sizeof(inputChar));
	printf("입력받은 문자열 : %s \n", inputChar);

	cout << "문자열을 입력하세요 \n";
	getline(cin, inputString);
	printf("입력받은 문자열 : %s \n", inputString.c_str());
	
	// to_string(value) : 정수형, 실수형 데이터를 문자열 데이터로 변경합니다.
	inputString = to_string(100);
	printf("문자열 변경 : %s \n", inputString.c_str());

	inputString = to_string(3.14);
	float myFloat = stof(inputString);
	printf("실수로 변경 : %.2f \n", myFloat);
	// stoi : string 을 int 로 변경
	// stod : string 을 double 로 변경
	// stoll : string 을 long long 으로 변경

	


	// 별도로 공부함
	cout << fixed;	// 소수점 고정
	cout.precision(5);	// 자릿수 고정 표현
	cout << inputString << endl;
	cout.unsetf(ios::fixed);	// 이전 cout 에 적용된 부분 해제

	return 0;
}