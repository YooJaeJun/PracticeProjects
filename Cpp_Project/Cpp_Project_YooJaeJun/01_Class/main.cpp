#include "struct/SampleStruct.h"
// 만든 설계도를 사용하기 위해 설계도가 선언되어 있는
// .h 를 포함시킵니다.
// Folder/ : 해당 폴더로 경로로 이동합니다.
#include "class/SampleClass.h"

int main()
{
	// 구조체 형식의 객체를 선언합니다.
	SampleStruct myStruct;
	myStruct.Public = 20;		// struct 에서 접근한자를 명시하지 않은 멤버이므로 
								// public 으로 선언이 되었기 때문에 외부에서 접근 가능
	// myStruct.A = 10;
	// myStruct.Print();		// private 로 선언되었기 때문에 외부에서 접근 불가능
	myStruct.B = 20;			// public 으로 선언되었기 때문에 외부에서 접근 가능

	// 클래스 형식의 객체를 선언합니다.
	SampleClass myClass;
	// myClass.Private = 20;	// class 에서 접근제한자를 명시하지 않은 멤버이므로
								// private 로 선언이 되었기 때문에 외부에서 접근 불가능
	myClass.A = 20;
	myClass.Print();			// public 으로 선언되었기 때문에 외부에서 접근 가능
	// myClass.B = 20;			// private 로 선언되었기 때문에 외부에서 접근 불가능
								

	return 0;
}