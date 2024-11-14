#include <iostream>
using namespace std;



int main()
{
    setlocale(LC_CTYPE, "rus");
    int n,tmp,*ptr=&tmp,max,min;
    cout << "Введите длину последовательности: ";
    cin >> n;
    cout << "Введите числа: ";
    cin >> *ptr;
    max = *ptr;
    min = *ptr;

    for (int i = 2; i <= n; i++)
    {
        cin >> *ptr;
        if (*ptr > max) { max = *ptr; }
        else if (*ptr < min) { min = *ptr; }
    }
    cout << "Максимальный элемент: " << max << endl;
    cout << "Минимальный элемент: " << min << endl;
    return 0;
}