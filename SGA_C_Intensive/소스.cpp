#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    long long sum = 1;
    for (long long i = 1; i <= n; i++)
    {
        sum *= i % 10;
    }
    return 0;
}