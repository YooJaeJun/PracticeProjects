// C 언어 => Base 가 되는 C++
// C 라는 언어가 베이스면서 class 가 추가된 C++
// 입출력, 함수, 구조체, 변수, 동적할당

// 목표 : 객체지향 프로그래밍 4대 특성
// 캡슐화, 추상화, 상속성, 다형성

// STL : 자료구조, 알고리즘

// C 언어에서 사용 가능했던 건 cpp 에서도 됩니다.
// 단, 말도 안되었던 오류들이 경고로 처리되었던 건 오류가 발생합니다.

// #include <stdio.h>
// C 언어 표준의 라이브러리 파일
#include <iostream>
// C++ 표준의 입출력 라이브러리 파일


int main()
{
	int input;
	// C 의 입력
	// printf("입력 : ");
	// scanf_s("%i", &input);
	// printf("input: %i \n", input);

	/*
	// C++ 의 입출력
	std::cout << "입력 : ";
	// std : 표준의
	// ::  : Scope 연산자
	// cout (console out) : 콘솔창에 출력합니다.
	// << (삽입 연산자) : 출력할 데이터를 넘기는 연산자입니다.
	std::cin >> input;
	// cin (console input) : 콘솔창에서 입력받습니다.
	// >> (추출 연산자) : 입력받은 데이터를 넘기는 연산자입니다.
	std::cout << "input : " << input << std::endl;
	// endl : '\n' (개행문자)의 기능을 가지고 있습니다.
	*/

	// C++ 의 입출력으로 실수형태의 값을 입력받고 출력해주세요.
	float f;
	std::cout << "f 입력 : ";
	std::cin >> f;
	std::cout << "f 출력 : " << f << '\n';

	// [ MyFloat : 3.14 ]
	std::cout << "[ f : " << f << " ]" << '\n';

	// 서식 문자('\n') 사용 가능
	// 형식 문자(%d,...) 사용 불가능
	return 0;
}