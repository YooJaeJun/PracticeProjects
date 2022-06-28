/*
	STL (Standard Template Library)
	프로그램에 필요한 자료구조와 알고리즘을 Template 형태로 제공하는 라이브러리 입니다.

	STL 구성
	Container, Container Adapter, Iterator, Algorithm, Functor, Allocator
	
	Container
	자료구조를 나타내며, 객체들을 저장하는 객체를 의미합니다.
	
	Container 종류
	- 시퀀스 컨테이너
	  자료를 선형 구조로 관리하는 컨테이너입니다.
	  선형적인 데이터 집합이므로, 데이터를 넣는 순서대로 요소가 할당됩니다.
	  특별한 제약이나, 관리 규칙 없이 데이터가 관리됩니다.
	  종류 : vector, list, deque

	- 연관 컨테이너
	  일정한 규칙에 따라 자료를 조직화하여 관리하는 컨테이너입니다.
	  key 와 value 를 통해 관계있는 값을 묶어서 관리합니다.
	  요소 탐색이 빠르고 삽입 / 제거가 느린 것이 특징입니다.


	Interface 란
	가상 소멸자와 순수 가상함수만 가지고 있는 클래스를 의미합니다.

	Container Adapter
	구성 요소의 인터페이스를 변경하여 새로운 인터페이스를 갖는 구성 요소로
	하는 것을 의미합니다.
	컨테이너를 변형하여 특정한 방식에 따라 관리하는 컨테이너
	- queue          : FIFO(First In First Out)방식으로 요소를 관리합니다.
	- priority_queue : 연산자를 설정함에 따라 요소 처리의 우선순위가 결정됩니다.
	- stack          : LIFO(Last In Last Out) 방식으로 요소를 관리합니다.

	FIFO : 처음 추가된 요소가 처음으로 나오는 방식
	LIFO : 마지막으로 추가된 요소가 처음으로 나오는 방식


	Iterator
	컨테이너에 있는 요소를 순회하거나, 접근할 수 있게 해주는 객체입니다.
	다음 요소로 이동할 경우 주소 연산자 (+, -, ++, --) 를 사용합니다.
	컨테이너 내부 객체에 접근할 때 * 연산자를 사용합니다.
	위의 모든 연산자를 연산자 오버로딩을 거칩니다.


	Functor : 연산자를 오버로딩한 클래스 객체를 의미합니다.
			  객체를 함수처럼 쓸 수 있는 기능을 가지고 있습니다.


	Algorithm : 컨테이너의 데이터를 다룰 수 있는 함수들을 의미합니다.


	Allocator : 컨테이너의 요소들을 할당하며 메모리를 관리하는 기능입니다.

*/

// 함수는 스택 방식
#include <iostream>
#include <string>
using namespace std;
struct Test
{
public:
	std::string Name;
	Test(std::string name)
	{
		Name = name;
		cout << Name << endl;
	}

};

void Func(Test test1, Test test2)
{

}

int main()
{
	Func(Test("test1"), Test("test2"));

	return 0;
}