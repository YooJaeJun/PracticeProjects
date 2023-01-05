#include <iostream>
#include <vector>
using namespace std;

// vector : �迭 ��� �����̳�
// ��Ҹ� ���� / ������ �� �ڵ����� �ڽ��� ũ�⸦ �����մϴ�.
// ��, ���� / ���� �� �ݺ��� ��ȿȭ ������ �Ͼ �� �ֽ��ϴ�.
// 
// �ݺ��� ��ȿȭ ����
// iterator �� �ش� ����� ��ġ�� ã�� ���ϴ� ������ �ǹ��մϴ�.

// #define INT
#define CLASS

class Monster
{
private:
	string Name;
	unsigned Lv;

public:
	Monster() = default;
	Monster(string Name, unsigned Lv)
	{
		// this Pointer : �ڱ� �ڽ��� ����Ű�� �������Դϴ�.
		this->Name = Name;
		this->Lv = Lv;
	}

	~Monster() = default;

	// ... c++ 17 �������� �ڵ����� ª�� �ڵ�� �ζ���ȭ
	__forceinline void Print() const
	{
		printf("[%s]::[Lv : %i] \n", Name.c_str(), Lv);
	}
};

template<typename T>
void PrintVector(vector<T> vec)
{
	// vector<T>::iterator iter;
	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
		iter->Print();
}

int main()
{
#ifdef INT
	// int ������ ������ �� �ִ� �迭 ��� �����̳��� vector vec �� �����մϴ�.
	vector<int> vec;

	// push_back(value) : vector �� �� �ڿ� ��Ҹ� �߰��մϴ�.
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	// begin() : �����̳��� ù��° ����� ��ġ�� ��ȯ�մϴ�.
	vector<int>::iterator iter = vec.begin();
	cout << "vector �� ù ��° ��� : " << *iter << endl;
	cout << "vector �� �� ��° ��� : " << vec[1] << endl;

	cout << endl;

	// end() : �����̳��� ������ ��� ��ġ�� ��ȯ�մϴ�.
	for (; iter != vec.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	// front() : �����̳��� ù ��° ��Ҹ� ��ȯ�մϴ�.
	cout << "vec.front() : " << vec.front() << endl;

	// pop_back() : ���������� �߰��� ��Ҹ� �����մϴ�.
	cout << "������ ��� ����" << endl;
	vec.pop_back();

	// back() : �����̳��� ������ ��Ҹ� ��ȯ�մϴ�.
	cout << "vec.back() : " << vec.back() << endl;

	// insert(where, value) : where ��ġ�� value ���� ���� ��Ҹ� �߰��մϴ�.
	vec.insert(vec.begin(), 20);

	for (iter = vec.begin(); iter != vec.end(); ++iter)
		cout << *iter << ' ';

	cout << endl;
	// erase(where) : where ��ġ�� �����ϴ� ��Ҹ� �����մϴ�.
	vec.erase(vec.begin());

	for (iter = vec.begin(); iter != vec.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	// size() : �����̳��� ��� ������ ��ȯ�մϴ�.
	cout << "vec.size() : " << vec.size() << endl;

	// clear() : �����̳��� ��Ҹ� ��� �����մϴ�.
	vec.clear();

	// empty() : �����̳��� ��Ұ� �����Ѵٸ� false, ����ִٸ� true �� ��ȯ�մϴ�.
	cout << "vec is Empty ? " << (vec.empty() ? "TRUE" : "FALSE") << endl;

	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	// at(index) : index ��ġ�� �����ϴ� ��Ҹ� ��ȯ�մϴ�.
	cout << "vec.at(2) : " << vec.at(2) << endl;
#endif

#ifdef CLASS
	vector<Monster> vec;
	Monster monster = { "������", 1 };
	vec.push_back(monster);
	vec.insert(vec.begin(), Monster("��", 3));
	PrintVector<Monster>(vec);

	cout << endl;

	vec[0].Print();
	vec.at(1).Print();
	
	cout << endl;

	vec.pop_back();
#endif

	return 0;
}