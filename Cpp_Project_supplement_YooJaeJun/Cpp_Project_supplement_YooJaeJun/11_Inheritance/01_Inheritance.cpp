#include <iostream>
using namespace std;

class Monster
{
private:
	string Name = "����ƺ�";
	int Hp = 10000;

public:
	void Damaged(int atk)
	{
		printf("%i �������� �Ծ����ϴ�. \n", atk);
		Hp -= atk;
		if (Hp <= 0) Hp = 0;
		printf("���� Hp : %i \n", Hp);
	}
};

class Character	// ĳ���� ������ ��� Ŭ���� �Դϴ�.
{
protected:
	string Name;
	unsigned Lv = 0;
	unsigned Hp = 0;
	unsigned Atk = 0;

public:
	Character()
	{
		cout << "ĳ���� �⺻ ������ ȣ��" << '\n';
	}
	Character(string name, unsigned lv, unsigned hp, unsigned atk) :
		Name(name), Lv(lv), Hp(hp), Atk(atk)
	{
		cout << "ĳ���� �����ε� ������ ȣ��" << '\n';
	}
	~Character() 
	{ 
		cout << "ĳ���� �Ҹ��� ȣ��" << '\n'; 
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
		printf("%s �� �����մϴ�. \n", Name.c_str());
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
		cout << "������ �⺻ ������ ȣ��" << '\n';
	}
	// ��ӿ��� �����ڴ� �ֻ��� ���Ŭ�������� ������ �Ļ� Ŭ���� ������ ȣ��˴ϴ�.

	~Warrior()
	{
		cout << "������ �Ҹ��� ȣ��" << '\n';
	}
	// ��ӿ��� �Ҹ��ڴ� ������ �Ļ�Ŭ�������� �ֻ��� ��� Ŭ���� ������ ȣ��˴ϴ�.

	// ������ ����Ʈ
	// �����ڸ� �����ϱ� ���� ������ ����� ����մϴ�.
	// ������ �ڿ� : �� �ۼ��Ͽ� ����մϴ�.
	// ���� ���� ������ ������� ���� �ʱ�ȭ ��Ų �� �������� ���Ǹ� �����մϴ�.
	Warrior(string name, unsigned lv, unsigned hp, unsigned atk, int str) :
		Character(name, lv, hp, atk) 
	{ STR = str; }
	/*
	Warrior(Character character, int str) :
		Character(character), STR(str) 
	{
		cout << "Warrior �����ε� ������ ȣ��" << '\n';
	}
	*/

public:
	// ��� Ŭ������ �޼��带 ������ �մϴ�.
	// �̸� �������̵��̶� �մϴ�.
	virtual void PrintCharacter() const
	{
		// Warrior ���Ŀ��� Character ������ ������ ������ �ְ�
		// Warrior �� PrintCharacter �� �ƴ�
		// Character ���Ŀ� �ִ� PrintCharacter �� ȣ���� �� �� �ֽ��ϴ�.
		Character::PrintCharacter();
		cout << "STR  : " << STR << '\n';
	}

	virtual int Attack() const
	{
		printf("%s �� �����մϴ�. \n", Name.c_str());
		return Atk + STR;
	}

	int Skill() const
	{
		printf("%s �� ��ų�� ����մϴ� ! \n", Name.c_str());
		return Atk * 2 + STR;
	}
};

// Character �� ��ӹ޴� Archer Ŭ������ ������ּ���.
// Archer �� �߰� �ɷ�ġ�� DEX �� �����ϴ�.
// Archer ��ü�� �����ϰ�
// PrintCharacter() �� ȣ���� �� Archer �� ������ �ִ� ��� ����� ���� ��µǵ��� ���ּ���.
// Skill() ����.

int main()
{
	// Character character = Character("ĳ����", 1, 10, 5);
	// character.PrintCharacter();

	// Warrior warrior("������", 5, 20, 10, 3);
	// warrior.PrintCharacter();
	// warrior.Attack();
	// warrior.Lv	// protected �� ������ ����̹Ƿ� ��ӹ��� Ŭ������ �ƴ� �ܺο��� ��� �Ұ�

	// �� ĳ���� : �Ļ� Ŭ������ ������ ��� Ŭ������ �������� ����Ű�� ���� ���մϴ�.
	Character* warrior = new Warrior("������", 1, 100, 10, 1);
	warrior->PrintCharacter();
	((Warrior*)warrior)->PrintCharacter();

	// �ٿ� ĳ���� : ��� Ŭ������ ������ �Ļ� Ŭ������ �������� ����Ű�� ���� ���մϴ�.
	// Warrior* character = new Character("������", 1, 100, 10, 1);
	// character->PrintCharacter();
	// ((Warrior*)character)->PrintCharacter();
	// Character* character = new Character("������", 1, 100, 10);
	// Warrior* down = (Warrior*)character;
	// down->PrintCharacter();

	// dynamic_cast<Warrior*>(warrior)->PrintCharacter();

	delete warrior;
	warrior = nullptr;

	return 0;
}

