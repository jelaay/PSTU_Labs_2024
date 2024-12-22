#include <cmath>
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    float n, s, a;
    int i = 1;
    bool flag = false;
    cin >> n >> s;
    while (i <= n && !flag)
    {
        a = sin(n + i / n);
        if (a == s) { flag = true; }
        else { i++; }
    }
    if (flag)
    {
        cout << "Элемент найден!" << endl;
    }
    else
    {
            cout << "Элемент не найден!" << endl;
    }
    return 0;
}

