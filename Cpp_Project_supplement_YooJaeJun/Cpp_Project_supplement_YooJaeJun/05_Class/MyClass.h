#pragma once

// 접근제한자 : class 나 struct 를 이루고 있는 멤버들의 
//				접근을 제한하는 키워드

// public: 외부에서 접근 가능
// private : 외부에서 접근 불가능, 
//			멤버함수의 정의 class 나 struct 의 코드블록에서만 접근 가능

// class 같은 경우 접근제한자를 명시하지 않는다면 private 로 선언됩니다.

class MyClass
{
public: 
	int A;
	void PrintA();

private:
	// 여기서부터 선언된 멤버들은 모두 private 가 됩니다.

	// 이와 같이 감추거나 공개할 멤버들을 묶어놓은 것을 객체지향의 4대속성 중
	// 캡슐화라 합니다.
};

// struct 같은 경우 접근제한자를 명시하지 않는다면 public 으로 선언됩니다.

struct MyStruct
{
private: 
	int A;
	void PrintA();
};


/*
객체 지향 4대 속성 중...
1. 캡슐화: 은닉성
2. 
3. 
4. 


객체 지향 프로그래밍 5대 원칙 Solid

*/