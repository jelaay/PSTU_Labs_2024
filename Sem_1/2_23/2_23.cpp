#include <cmath>
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    float n, a, max;
    int i = 2;
    int count = 1;
    cin >> n;
    max = sin(n + 1 / n);
    while (i <= n)
    {
        a = sin(n + i / n);
        if (a > max)
        {
            max = a;
            count = 1;
        }
        else if (a == max) { count++; }
        i++;
    }
    cout << "Максимальный элемент: " << max << endl;
    cout << "Число элементов с этим значением: " << count << endl;
}
