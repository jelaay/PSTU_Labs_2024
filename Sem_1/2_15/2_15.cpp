﻿#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n, s, tmp; 
    bool flag;
    cout << "Введите натуральное число N: ";
    cin >> n;
    cout << "Введите цифру S: ";
    cin >> s;
    tmp = 0;
    flag = false;
    while (n != 0)
    {
        tmp = n % 10;
        n /=10;
        if (tmp == s)
        {
            flag = true;
        }
    }
    if (flag) { cout << "Цифра S входит в запись числа N." << endl; }
    else { cout << "Цифра S не входит в запись числа N." << endl; }
    return 0;
}
