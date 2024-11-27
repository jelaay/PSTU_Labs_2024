#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE,"rus");
    int n, min, max,tmp;
    cout << "Введите длину последовательности: ";
    cin >> n;
    cout << "Введите 1 число последовательности: ";
    cin >> max;
    min = max;
    for (int i = 1; i < n; i++)
    {
        cout << "Введите "<<i+1<< " число последовательности: ";
        cin >> tmp;
        if (tmp > max)
        {
            max = tmp;
        }
        else if (tmp < min)
        {
            min = tmp;
        }
    }
    cout << "Сумма максимального и минимального элементов последовательности: " << min + max << endl;
    return 0;
}
