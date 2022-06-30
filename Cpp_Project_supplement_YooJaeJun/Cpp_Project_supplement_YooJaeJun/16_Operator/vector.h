#pragma once
#include <iostream>
#include <string>
using namespace std;

// 연산자 오버로딩 (Operator Overloading)
// 기존에 존재하던 연산자의 기본 기능 이외에 다른 기능을 추가하는 것을 의미합니다.

// 다음과 같은 연산자는 오버로딩이 불가능합니다.
// - .  : 멤버 선택
// - :: : 범위 지정
// - ?  : 조건
// - #  : 문자열 전처리기 변환
// - ## : 전처리기 연결
// - static_cast
// - dynamic_cast
// - const_cast
// - reinterpret_cast
// - sizeof


class Vector final
{
public:
	float X;
	float Y;
	unsigned Name = 0;

public: 
	Vector() : X(0.f), Y(0.f) {}
	Vector(const float& x, const float& y) : X(x), Y(y) {}

	__forceinline void PrintVector() const
	{
		printf("vec%i : [ %.1f, %.1f ] \n", Name, X, Y);
	}

	__forceinline void Set(int name)
	{
		Name = name;
	}
	
public:
	// 연산자 오버로딩 방법
	// 반환 타입 / operator"오버로딩할 연산자" / (피연산자)

#pragma region Arithmetic Operator
	// +
	__forceinline Vector operator+(const Vector& value)
	{
		return Vector(X + value.X, Y + value.Y);
	}
	__forceinline Vector operator+(const float& value)
	{
		return Vector(X + value, Y + value);
	}

	// -
	__forceinline Vector operator-(const Vector& value)
	{
		return Vector(X - value.X, Y - value.Y);
	}
	__forceinline Vector operator-(const float& value)
	{
		return Vector(X - value, Y - value);
	}

	// *
	__forceinline Vector operator*(const Vector& value)
	{
		return Vector(X * value.X, Y * value.Y);
	}
	__forceinline Vector operator*(const float& value)
	{
		return Vector(X * value, Y * value);
	}

	// /
	__forceinline Vector operator/(const Vector& value)
	{
		return Vector(X / value.X, Y / value.Y);
	}
	__forceinline Vector operator/(const float& value)
	{
		return Vector(X / value, Y / value);
	}
#pragma endregion

#pragma region Assignment Operator
	// +=
	__forceinline void operator+=(const Vector& value)
	{
		X += value.X;
		Y += value.Y;
	}
	__forceinline void operator+=(const float& value)
	{
		X += value;
		Y += value;
	}

	// -=
	__forceinline void operator-=(const Vector& value)
	{
		X -= value.X;
		Y -= value.Y;
	}
	__forceinline void operator-=(const float& value)
	{
		X -= value;
		Y -= value;
	}

	// *=
	__forceinline void  operator*=(const Vector& value)
	{
		X *= value.X;
		Y *= value.Y;
	}
	__forceinline void  operator*=(const float& value)
	{
		X *= value;
		Y *= value;
	}

	// /=
	__forceinline void  operator/=(const Vector& value)
	{
		X /= value.X;
		Y /= value.Y;
	}
	__forceinline void  operator/=(const float& value)
	{
		X /= value;
		Y /= value;
	}
#pragma endregion

#pragma region Increment & decrement operator
	// 전위 증감 연산자
	__forceinline void operator++()
	{
		++X;
		++Y;
	}
	__forceinline void operator--()
	{
		--X;
		--Y;
	}
	
	// 후위 증감 연산자
	__forceinline void operator++(int)
	{
		X++;
		Y++;
	}
	__forceinline void operator--(int)
	{
		X--;
		Y--;
	}

#pragma endregion

	__forceinline bool operator==(const Vector& value)
	{
		return (X == value.X && Y == value.Y);
	}
	__forceinline bool operator!=(const Vector& value)
	{
		return (X != value.X && Y != value.Y);
	}

	void operator()()
	{
		PrintVector();
	}

	void operator[](float value)
	{
		PrintVector();
	}

	void operator+()
	{
	}
	void operator-()
	{
		X = -X;
		Y = -Y;
	}

	// 관계 연산자. 아래는 내 기준이고, 강사님은 멤버들의 합 간 비교
	bool operator<(const Vector& value)
	{
		return X < value.X && Y < value.Y;
	}
	bool operator<=(const Vector& value)
	{
		return X <= value.X && Y <= value.Y;
	}
	bool operator>(const Vector& value)
	{
		return X > value.X && Y > value.Y;
	}
	bool operator>=(const Vector& value)
	{
		return X >= value.X && Y >= value.Y;
	}

	void operator>>(const int& value)
	{
		X += value;
		Y += value;
	}
	void operator<<(const int& value)
	{
		X -= value;
		Y -= value;
	}

	void operator~()
	{
		float temp = X;
		X = Y;
		Y = temp;
	}
};
