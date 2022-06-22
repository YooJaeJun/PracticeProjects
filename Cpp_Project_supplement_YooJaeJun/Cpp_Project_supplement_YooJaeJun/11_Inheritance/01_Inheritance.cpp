#include <iostream>
using namespace std;

class Monster
{
private:
	string Name = "허수아비";
	int Hp = 10000;

public:
	void Damaged(int atk)
	{
		printf("%i 데미지를 입었습니다. \n", atk);
		Hp -= atk;
		if (Hp <= 0) Hp = 0;
		printf("남은 Hp : %i \n", Hp);
	}
};

class Character	// 캐릭터 형식의 기반 클래스 입니다.
{
protected:
	string Name;
	unsigned Lv = 0;
	unsigned Hp = 0;
	unsigned Atk = 0;

public:
	Character()
	{
		cout << "캐릭터 기본 생성자 호출" << '\n';
	}
	Character(string name, unsigned lv, unsigned hp, unsigned atk) :
		Name(name), Lv(lv), Hp(hp), Atk(atk)
	{
		cout << "캐릭터 오버로딩 생성자 호출" << '\n';
	}
	~Character() 
	{ 
		cout << "캐릭터 소멸자 호출" << '\n'; 
	}

public:
	void PrintCharacter() const
	{
		cout << "Name : " << Name << '\n';
		cout << "Lv   : " << Lv << '\n';
		cout << "Hp   : " << Hp << '\n';
		cout << "Atk  : " << Atk << '\n';
	}

	virtual int Attack() const
	{
		printf("%s 가 공격합니다. \n", Name.c_str());
		return Atk;
	}
};

class Warrior : public Character
{
private:
	int STR = 0;

public:
	Warrior()
	{
		cout << "워리어 기본 생성자 호출" << '\n';
	}
	// 상속에서 생성자는 최상위 기반클래스부터 최하위 파생 클래스 순서로 호출됩니다.

	~Warrior()
	{
		cout << "워리어 소멸자 호출" << '\n';
	}
	// 상속에서 소멸자는 최하위 파생클래스부터 최상위 기반 클래스 순서로 호출됩니다.

	// 생성자 리스트
	// 생성자를 실행하기 전에 실행할 명령을 등록합니다.
	// 생성자 뒤에 : 을 작성하여 사용합니다.
	// 받은 인자 값으로 멤버들을 먼저 초기화 시킨 후 생성자의 정의를 실행합니다.
	Warrior(string name, unsigned lv, unsigned hp, unsigned atk, int str) :
		Character(name, lv, hp, atk) 
	{ STR = str; }
	/*
	Warrior(Character character, int str) :
		Character(character), STR(str) 
	{
		cout << "Warrior 오버로딩 생성자 호출" << '\n';
	}
	*/

public:
	// 기반 클래스의 메서드를 재정의 합니다.
	// 이를 오버라이딩이라 합니다.
	virtual void PrintCharacter() const
	{
		// Warrior 형식에선 Character 형식의 구조를 가지고 있고
		// Warrior 의 PrintCharacter 가 아닌
		// Character 형식에 있는 PrintCharacter 를 호출해 줄 수 있습니다.
		Character::PrintCharacter();
		cout << "STR  : " << STR << '\n';
	}

	virtual int Attack() const
	{
		printf("%s 가 공격합니다. \n", Name.c_str());
		return Atk + STR;
	}

	int Skill() const
	{
		printf("%s 가 스킬을 사용합니다 ! \n", Name.c_str());
		return Atk * 2 + STR;
	}
};

// Character 를 상속받는 Archer 클래스를 만들어주세요.
// Archer 는 추가 능력치로 DEX 를 가집니다.
// Archer 객체를 생성하고
// PrintCharacter() 를 호출할 시 Archer 가 가지고 있는 모든 멤버의 값이 출력되도록 해주세요.
// Skill() 까지.

int main()
{
	// Character character = Character("캐릭터", 1, 10, 5);
	// character.PrintCharacter();

	// Warrior warrior("워리어", 5, 20, 10, 3);
	// warrior.PrintCharacter();
	// warrior.Attack();
	// warrior.Lv	// protected 로 설정한 멤버이므로 상속받은 클래스가 아닌 외부에서 사용 불가

	// 업 캐스팅 : 파생 클래스의 형식을 기반 클래스의 형식으로 가리키는 것을 말합니다.
	Character* warrior = new Warrior("워리어", 1, 100, 10, 1);
	warrior->PrintCharacter();
	((Warrior*)warrior)->PrintCharacter();

	// 다운 캐스팅 : 기반 클래스의 형식을 파생 클래스의 형식으로 가리키는 것을 말합니다.
	// Warrior* character = new Character("워리어", 1, 100, 10, 1);
	// character->PrintCharacter();
	// ((Warrior*)character)->PrintCharacter();
	// Character* character = new Character("워리어", 1, 100, 10);
	// Warrior* down = (Warrior*)character;
	// down->PrintCharacter();

	// dynamic_cast<Warrior*>(warrior)->PrintCharacter();

	delete warrior;
	warrior = nullptr;

	return 0;
}

