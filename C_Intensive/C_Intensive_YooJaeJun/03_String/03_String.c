#include <stdio.h>
#include <locale.h>

int main()
{
	// 아스키 코드
	// 알파벳, 숫자, 특수기호, 공백문자, 제어문자를 
	// 컴퓨터에게 숫자 데이터로 알려주기 위해서 생겨난 코드입니다.
	char A = 'A';

	printf("%c \n", A);
	printf("%d \n", A);
	printf("%c \n", 'A');
	printf("%d \n", 'A');

	"ABC";
	// 'ㄱ';
	// '가';
	// '값';
	// 'ㄱㅏㅂㅅ'

	3.14;
	3.14f;

	setlocale(LC_ALL, "KOREAN");

	// 와이드 캐릭터
	wchar_t Korea = L'값';
	printf("wchar_t Size : %zi \n", sizeof(wchar_t));	// 32,768 가지의 문자를 표기할 수 있음
	char myChar = 'A';
	wprintf(L"%c \n", Korea);
	wprintf(L"%c \n", myChar);

	const char* str = "가나다라";	// 멀티바이트 집합 문자 사용 옵션 시 한글 한 글자당 2byte씩
	printf("%s \n", str);

	return 0;
}