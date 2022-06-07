#include <iostream>
using namespace std;

// 사용자정의자료형 구조체를 사용하여 Dog 라는 설계도를 설계합니다.
struct Dog
{
	// string : 문자형식의 데이터를 저장할 수 있는 설계도입니다.
	string Name;	// 이름을 저장할 멤버 변수
	int	   Age;		// 나이를 저장할 멤버 변수
	// 멤버 : 설계도로 이루는 구성 요소를 뜻합니다.

};

// Human 이라는 설계도를 작성하여 객체를 만들고 해당 객체의 멤버들을 출력해주세요
// 이름, 나이, 성별, 키
struct human
{
private:
	string name;
	int age;
	string sex;
	double height;

public:
	inline human() : name(""), age(0), sex(""), height(0.0) {}
	inline human(const string name, const int age, const string sex, const double height)
	{
		this->name = name;
		this->age = age;
		this->sex = sex;
		this->height = height;
	}

public:
	inline void printInfo()
	{
		cout << "이름 : " << name << '\n';
		cout << "나이 : " << age << '\n';
		cout << "성별 : " << sex << '\n';
		cout << "키   : " << height << '\n';
	}
};

int main()
{
	/*
	// 정수형 데이터를 -21억 ~ +21억 사이의 값을 저장할 수
	// 있는 설계도인 int 를 사용하여 A 와 B 라는 객체를 만듭니다.
	int A = 10;
	int B = 10;

	A = 20;

	printf("A : %i \n", A);
	printf("B : %i \n", B);

	// 같은 설계도로 객체를 만들더라도 하나의 객체가 변경되었을 때
	// 다른 객체 또한 변경되지 않는 것이 객체의 속성입니다.

	// Dog 라는 설계도로 객체를 만듭니다.
	Dog dog_1 = { "MyDog", 10 };
	Dog dog_2;
	
	dog_2.Name = "YourDog";
	// . (멤버 직접 접근 연산자)
	// 구조체(설계도)를 이루고 있는 특정 멤버에 접근할 수 있게 해주는 연산자입니다.
	dog_2.Age = 5;

	cout << "Name : " << dog_1.Name << endl;
	cout << "Age : " << dog_1.Age << endl;
	cout << "Name : " << dog_2.Name << endl;
	cout << "Age : " << dog_2.Age << endl;
	cout << '\n';
	*/


	human yoojaejun("유재준", 29, "남자", 170.22);
	yoojaejun.printInfo();

	return 0;
}