#include <iostream>
using namespace std;

typedef unsigned long long BLONG;

struct Matrix
{
	BLONG data[2][2];

	static Matrix Multiply(const Matrix& a, const Matrix& b)
	{
		Matrix r;

		r.data[0][0] = a.data[0][0] * b.data[0][0] + a.data[0][1] * b.data[1][0];
		r.data[0][1] = a.data[0][0] * b.data[1][0] + a.data[0][1] * b.data[1][1];

		r.data[1][0] = a.data[1][0] * b.data[0][0] + a.data[1][1] * b.data[1][0];
		r.data[1][1] = a.data[1][0] * b.data[1][0] + a.data[1][1] * b.data[1][1];

		return r;
	}
};

Matrix Power(Matrix m, int n)
{
	if (n <= 1)
		return m;

	m = Power(m, n / 2);
	m = Matrix::Multiply(m, m);

	if (n & 1)
	{
		Matrix b;
		b.data[0][0] = 1; b.data[0][1] = 1;
		b.data[1][0] = 1; b.data[1][1] = 0;

		m = Matrix::Multiply(m, b);
	}

	return m;
}

BLONG Fibonacci(int n)
{
	Matrix m;

	m.data[0][0] = 1; m.data[0][1] = 1;
	m.data[1][0] = 1; m.data[1][1] = 0;

	m = Power(m, n);

	return m.data[0][1];
}

int main()
{
	BLONG temp = Fibonacci(10);
	cout << temp;
}