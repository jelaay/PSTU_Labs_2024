#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n,tmp, maxx;
    cout << "Введите количество элементов последовательности: ";
    cin >> n;
    cout << endl;
    cout << "Введите " << 1 << " элемент последовательности: ";
    cin >> maxx;
    cout << endl;
    for (int i = 1; i <= n-1; i++)
    {
        cout << "Введите "<<i+1<<" элемент последовательности: ";
        cin >> tmp;
        cout << endl;
        if (tmp > maxx)
        {
            maxx = tmp;
        }
    }
    cout << "Максимальное число в последовательности: " << maxx << endl;
    return 0;
}