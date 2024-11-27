#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n, sum, tmp;
    cout << "Введите натуральное число N: ";
    cin >> n;
    sum = 0;
    tmp = 0;
    while (n != 0)
    {
        tmp = n % 10;
        sum += tmp;
        n /= 10;
    }
    cout << "Cумма цифр введённого числа: " << sum << endl;
    return 0;
}

