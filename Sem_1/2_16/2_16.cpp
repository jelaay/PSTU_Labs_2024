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
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 != 0)
        {
            sum = sum - i;
        }
        else { sum = sum + i; }
    }
    cout << "Cумма N цифр по заданному правилу равна: " << sum << endl;
    return 0;
}