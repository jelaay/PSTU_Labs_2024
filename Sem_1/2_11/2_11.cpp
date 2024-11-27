#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n, tmp;
    bool flagplus=false;
    bool flagminus=false;
    cout << "Введите количество элементов последовательности: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << "Введите " << i << " элемент последовательности: ";
        cin >> tmp;
        if (!flagplus && !flagminus)
        {
            if (tmp > 0) { flagplus = true; }
            else if (tmp < 0) { flagminus = true; }
        }
    }
    if (flagplus) { cout << "Сначала ввели положительное число"; }
    else if (flagminus) { cout << "Сначала ввели отрицательное число"; }
    else { cout << "Все элементы были нулевыми"; }
    cout << endl;
    return 0;
}