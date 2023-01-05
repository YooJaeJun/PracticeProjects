#include "vector.h"
using namespace std;

int main()
{
	Vector vec1 = Vector(1.f, 1.f) + Vector(1.f, 1.f);
	vec1.Set(1);
	vec1.PrintVector();

	Vector vec2 = Vector(1.f, 1.f) + 2.f;	// x + float, y + float
	vec2.Set(2);
	vec2.PrintVector();

	Vector vec3 = Vector(1.f, 1.f) - 2.f;
	vec3.Set(3);
	vec3.PrintVector();
	Vector vec4 = Vector(1.f, 1.f) * 2.f;
	vec4.Set(4);
	vec4.PrintVector();
	Vector vec5 = Vector(1.f, 1.f) / 2.f;
	vec5.Set(5);
	vec5.PrintVector();

	cout << endl;

	int a = 1;
	a += 1;

	vec1 += Vector(3.f, 3.f);	// vec2 += vec1;
	vec1.PrintVector();
	vec2 -= Vector(3.f, 3.f);
	vec2.PrintVector();
	vec3 *= Vector(3.f, 3.f);
	vec3.PrintVector();
	vec4 /= Vector(3.f, 3.f);
	vec4.PrintVector();

	cout << endl;

	++vec1;
	vec1.PrintVector();
	vec1++;
	vec1.PrintVector();

	cout << endl;

	cout << "vec1 == vec1 ? " << (vec1 == vec1) << endl;
	cout << "vec1 == vec2 ? " << (vec1 == vec2) << endl;
	cout << "vec1 != vec1 ? " << (vec1 != vec1) << endl;
	cout << "vec1 != vec2 ? " << (vec1 != vec2) << endl;

	cout << endl;

	vec1();
	vec1[2.2f];

	cout << endl;

	-vec1;
	vec1.PrintVector();

	cout << "vec1 < vec2 : " << (vec1 < vec2) << endl;

	cout << endl;

	vec1 = { 3.f, 1.f };
	vec1 >> 4;
	vec1();

	~vec1;
	vec1();
}