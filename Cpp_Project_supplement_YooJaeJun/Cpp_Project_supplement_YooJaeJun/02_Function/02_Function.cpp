// Monster 라는 구조체를 선언하고
// Monster 형식의 객체인 slime 과 fairy 를 만들어주세요.

// Monster 의 멤버로는
// 멤버 변수 : 이름, 공격력, 체력
// 멤버  함수 : 공격

// 공격 함수를 호출했을 때
// slime 의 경우 : 슬라임 이(가) 공격합니다.
// fairy 의 경우 : 페어리 이(가) 공격합니다.
// 를 호출하세요.

// Fairy 와 Slime 구조체를 선언하고
// 각각 멤버 변수로 이름, 공격력, 체력을 가집니다.
// 멤버함수로는 공격을 동일하게 가집니다.
// Fairy 형식과 Slime 형식의 객체를 선언하고 공격 함수를 아래와 같이 호출되도록
// 만들어주세요.
// Fairy 형식의 객체의 경우 : 페어리가 마법으로 공격합니다.
// Slime 형식의 객체의 경우 : 슬라임이 몸통으로 공격합니다.

#include <iostream>
using namespace std;

class Monster
{
protected:
	string name;
	int atk;
	int hp;

public:
	Monster() : name(""), atk(0), hp(0) {}
	Monster(const string name, const int atk, const int hp) : name(name), atk(atk), hp(hp) {}

public:
	inline void Attack() const
	{
		cout << name << "이(가) " << atk << "의 공격력으로 공격합니다.\n";
	}
};

class Fairy : public Monster
{
public:
	Fairy() : Monster() {}
	Fairy(const Monster& monster) : Monster(monster) {}

public:
	inline void Attack() const
	{
		cout << name << "이 " << "마법으로 공격합니다." << "(공격력 : " << atk << ")" << '\n';
	}
};

class Slime : public Monster
{
public:
	Slime() : Monster() {}
	Slime(const Monster& monster) : Monster(monster) {}

public:
	inline void Attack() const
	{
		cout << name << "가 " << "몸통으로 공격합니다." << "(공격력 : " << atk << ")" << '\n';
	}
};

int main()
{
	/*
	Monster fairy({ "슬라임", 10, 100 });
	Monster slime({ "페어리", 20, 60 });
	fairy.Attack();
	slime.Attack();
	*/

	Fairy fairy({ "슬라임", 10, 100 });
	Slime slime({ "페어리", 20, 60 });
	fairy.Attack();
	slime.Attack();

	return 0;
}