#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n;
    float sum, x, fact;

    cout << "Введите значение X: ";
    cin >> x;
    cout << "Введите значение N: ";
    cin >> n;

    sum = 1 + x;
    fact = 1;

    for (int i = 2; i <= n; i++)
    {
        fact = fact * i;
        sum = sum + ((pow(x, i)) / fact);
    }
    cout << "" << sum;
    return 0;
}

