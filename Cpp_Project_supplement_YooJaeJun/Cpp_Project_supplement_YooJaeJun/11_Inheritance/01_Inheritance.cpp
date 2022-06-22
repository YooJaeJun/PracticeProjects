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
		cout << "Character �⺻ ������ ȣ��" << '\n';
	}
	Character(const string name, const unsigned lv, const unsigned hp, const unsigned atk) :
		Name(name), Lv(lv), Hp(hp), Atk(atk)
	{
		cout << "Character �����ε� ������ ȣ��" << '\n';
	}
	virtual ~Character()
	{
		cout << "Character �Ҹ��� ȣ��" << '\n';
	}

public:
	virtual void PrintCharacter() const
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
	unsigned STR = 0;

public:
	Warrior()
	{
		cout << "Warrior �⺻ ������ ȣ��" << '\n';
	}
	// ��ӿ��� �����ڴ� �ֻ��� ���Ŭ�������� ������ �Ļ� Ŭ���� ������ ȣ��˴ϴ�.

	virtual ~Warrior()
	{
		cout << "Warrior �Ҹ��� ȣ��" << '\n';
	}
	// ��ӿ��� �Ҹ��ڴ� ������ �Ļ�Ŭ�������� �ֻ��� ��� Ŭ���� ������ ȣ��˴ϴ�.

	// ������ ����Ʈ
	// �����ڸ� �����ϱ� ���� ������ ����� ����մϴ�.
	// ������ �ڿ� : �� �ۼ��Ͽ� ����մϴ�.
	// ���� ���� ������ ������� ���� �ʱ�ȭ ��Ų �� �������� ���Ǹ� �����մϴ�.
	Warrior(const string name, const unsigned lv, const unsigned hp, const unsigned atk, const unsigned str) :
		Character(name, lv, hp, atk)
	{
		STR = str;
	}
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
	virtual void PrintCharacter() const override
	{
		// Warrior ���Ŀ��� Character ������ ������ ������ �ְ�
		// Warrior �� PrintCharacter �� �ƴ�
		// Character ���Ŀ� �ִ� PrintCharacter �� ȣ���� �� �� �ֽ��ϴ�.
		Character::PrintCharacter();
		cout << "STR  : " << STR << '\n';
	}

	virtual int Attack() const override
	{
		Character::Attack();
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

class Archer : public Character
{
private:
	unsigned DEX = 0;

public:
	Archer()
	{ cout << "Archer �⺻ ������ ȣ��" << '\n'; }

	explicit Archer(const string name, const unsigned lv, const unsigned hp, const unsigned atk, const unsigned dex) :
		Character(name, lv, hp, atk), DEX(dex)
	{ cout << "Archer �����ε� ������ ȣ��" << '\n'; }

	virtual ~Archer()
	{ cout << "Archer �Ҹ��� ȣ��" << '\n'; }

public:
	virtual void PrintCharacter() const override
	{
		Character::PrintCharacter();
		cout << "DEX  : " << DEX << '\n';
	}

	virtual int Attack() const override
	{
		Character::Attack();
		return Atk + DEX;
	}

	int Skill() const
	{
		printf("%s �� ��ų�� ����մϴ� ! \n", Name.c_str());
		return Atk * 2 + DEX;
	}
};

int main()
{
	// Character character = Character("ĳ����", 1, 10, 5);
	// character.PrintCharacter();

	// Warrior warrior("������", 5, 20, 10, 3);
	// warrior.PrintCharacter();
	// warrior.Attack();
	// warrior.Lv	// protected �� ������ ����̹Ƿ� ��ӹ��� Ŭ������ �ƴ� �ܺο��� ��� �Ұ�

	// �� ĳ���� : �Ļ� Ŭ������ ������ ��� Ŭ������ �������� ����Ű�� ���� ���մϴ�.
	// Character* warrior = new Warrior("������", 1, 100, 10, 1);
	// warrior->PrintCharacter();
	// ((Warrior*)warrior)->PrintCharacter();

	// �ٿ� ĳ���� : ��� Ŭ������ ������ �Ļ� Ŭ������ �������� ����Ű�� ���� ���մϴ�.
	// Warrior* character = new Character("������", 1, 100, 10, 1);
	// character->PrintCharacter();
	// ((Warrior*)character)->PrintCharacter();
	// Character* character = new Character("������", 1, 100, 10);
	// Warrior* down = (Warrior*)character;
	// down->PrintCharacter();

	// dynamic_cast<Warrior*>(warrior)->PrintCharacter();


	Character* archer = new Archer("�ü�", 1, 100, 10, 1);
	archer->PrintCharacter();

	delete archer;
	archer = nullptr;

	// delete warrior;
	// warrior = nullptr;

	return 0;
}

