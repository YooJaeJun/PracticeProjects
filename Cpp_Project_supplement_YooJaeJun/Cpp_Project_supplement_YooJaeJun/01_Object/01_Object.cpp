#include <iostream>
using namespace std;

// ����������ڷ��� ����ü�� ����Ͽ� Dog ��� ���赵�� �����մϴ�.
struct Dog
{
	// string : ���������� �����͸� ������ �� �ִ� ���赵�Դϴ�.
	string Name;	// �̸��� ������ ��� ����
	int	   Age;		// ���̸� ������ ��� ����
	// ��� : ���赵�� �̷�� ���� ��Ҹ� ���մϴ�.

};

// Human �̶�� ���赵�� �ۼ��Ͽ� ��ü�� ����� �ش� ��ü�� ������� ������ּ���
// �̸�, ����, ����, Ű
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
		cout << "�̸� : " << name << '\n';
		cout << "���� : " << age << '\n';
		cout << "���� : " << sex << '\n';
		cout << "Ű   : " << height << '\n';
	}
};

int main()
{
	/*
	// ������ �����͸� -21�� ~ +21�� ������ ���� ������ ��
	// �ִ� ���赵�� int �� ����Ͽ� A �� B ��� ��ü�� ����ϴ�.
	int A = 10;
	int B = 10;

	A = 20;

	printf("A : %i \n", A);
	printf("B : %i \n", B);

	// ���� ���赵�� ��ü�� ������� �ϳ��� ��ü�� ����Ǿ��� ��
	// �ٸ� ��ü ���� ������� �ʴ� ���� ��ü�� �Ӽ��Դϴ�.

	// Dog ��� ���赵�� ��ü�� ����ϴ�.
	Dog dog_1 = { "MyDog", 10 };
	Dog dog_2;
	
	dog_2.Name = "YourDog";
	// . (��� ���� ���� ������)
	// ����ü(���赵)�� �̷�� �ִ� Ư�� ����� ������ �� �ְ� ���ִ� �������Դϴ�.
	dog_2.Age = 5;

	cout << "Name : " << dog_1.Name << endl;
	cout << "Age : " << dog_1.Age << endl;
	cout << "Name : " << dog_2.Name << endl;
	cout << "Age : " << dog_2.Age << endl;
	cout << '\n';
	*/


	human yoojaejun("������", 29, "����", 170.22);
	yoojaejun.printInfo();

	return 0;
}