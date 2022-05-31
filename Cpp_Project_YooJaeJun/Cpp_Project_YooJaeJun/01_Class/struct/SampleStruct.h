#pragma once
#include <iostream>
using namespace std;

struct SampleStruct
{
	// struct 와 같은 경우 접근제한자를 명시하지 않는다면 멤버들은 public 이 됩니다.
	int Public = 0;

private :	// 아래에 모든 멤버를 외부에서 접근할 수 없는 멤버로 설저합니다.
	int A = 10;

	void Print();

public :	// 아래에 모든 멤버를 외부에서 접근할 수 있는 멤버로 설정합니다.
	int B = 20;
};

