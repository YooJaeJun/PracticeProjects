#pragma once
#include <iostream>
#include <string>
using namespace std;

// ������ �����ε� (Operator Overloading)
// ������ �����ϴ� �������� �⺻ ��� �̿ܿ� �ٸ� ����� �߰��ϴ� ���� �ǹ��մϴ�.

// ������ ���� �����ڴ� �����ε��� �Ұ����մϴ�.
// - .  : ��� ����
// - :: : ���� ����
// - ?  : ����
// - #  : ���ڿ� ��ó���� ��ȯ
// - ## : ��ó���� ����
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
	// ������ �����ε� ���
	// ��ȯ Ÿ�� / operator"�����ε��� ������" / (�ǿ�����)

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
	// ���� ���� ������
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
	
	// ���� ���� ������
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

	// ���� ������. �Ʒ��� �� �����̰�, ������� ������� �� �� ��
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
