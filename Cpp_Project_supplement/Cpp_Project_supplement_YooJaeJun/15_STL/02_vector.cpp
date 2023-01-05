#include <iostream>
#include <vector>
using namespace std;

// vector : 배열 기반 컨테이너
// 요소를 삽입 / 제거할 때 자동으로 자신의 크기를 조정합니다.
// 단, 삽입 / 제거 시 반복자 무효화 현상이 일어날 수 있습니다.
// 
// 반복자 무효화 현상
// iterator 가 해당 요소의 위치를 찾지 못하는 현상을 의미합니다.

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
		// this Pointer : 자기 자신을 가리키는 포인터입니다.
		this->Name = Name;
		this->Lv = Lv;
	}

	~Monster() = default;

	// ... c++ 17 기준으로 자동으로 짧은 코드는 인라인화
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
	// int 형식을 저장할 수 있는 배열 기반 컨테이너인 vector vec 를 선언합니다.
	vector<int> vec;

	// push_back(value) : vector 의 맨 뒤에 요소를 추가합니다.
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	// begin() : 컨테이너의 첫번째 요소의 위치를 반환합니다.
	vector<int>::iterator iter = vec.begin();
	cout << "vector 의 첫 번째 요소 : " << *iter << endl;
	cout << "vector 의 두 번째 요소 : " << vec[1] << endl;

	cout << endl;

	// end() : 컨테이너의 마지막 요소 위치를 반환합니다.
	for (; iter != vec.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	// front() : 컨테이너의 첫 번째 요소를 반환합니다.
	cout << "vec.front() : " << vec.front() << endl;

	// pop_back() : 마지막으로 추가한 요소를 제거합니다.
	cout << "마지막 요소 제거" << endl;
	vec.pop_back();

	// back() : 컨테이너의 마지막 요소를 반환합니다.
	cout << "vec.back() : " << vec.back() << endl;

	// insert(where, value) : where 위치에 value 값을 가진 요소를 추가합니다.
	vec.insert(vec.begin(), 20);

	for (iter = vec.begin(); iter != vec.end(); ++iter)
		cout << *iter << ' ';

	cout << endl;
	// erase(where) : where 위치에 존재하는 요소를 제거합니다.
	vec.erase(vec.begin());

	for (iter = vec.begin(); iter != vec.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	// size() : 컨테이너의 요소 개수를 반환합니다.
	cout << "vec.size() : " << vec.size() << endl;

	// clear() : 컨테이너의 요소를 모두 제거합니다.
	vec.clear();

	// empty() : 컨테이너의 요소가 존재한다면 false, 비어있다면 true 를 반환합니다.
	cout << "vec is Empty ? " << (vec.empty() ? "TRUE" : "FALSE") << endl;

	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	// at(index) : index 위치에 존재하는 요소를 반환합니다.
	cout << "vec.at(2) : " << vec.at(2) << endl;
#endif

#ifdef CLASS
	vector<Monster> vec;
	Monster monster = { "슬라임", 1 };
	vec.push_back(monster);
	vec.insert(vec.begin(), Monster("페어리", 3));
	PrintVector<Monster>(vec);

	cout << endl;

	vec[0].Print();
	vec.at(1).Print();
	
	cout << endl;

	vec.pop_back();
#endif

	return 0;
}