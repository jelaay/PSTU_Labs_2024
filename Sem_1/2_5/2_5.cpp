#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n, k, z;
    cout << "Введите основание треугольника, оно должно быть больше двух: ";
    cin >> n;
    k = 1;
    z = n-(n-1);
    if (n>2)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= (n-k); j++)
            {
                cout << " ";
            }
            k += 1;
            for (int g = 1; g <= z; g++)
            {
                cout << "*";
            }
            z = z + 1;
            cout << "" << endl;
        }
    }
    else { cout << "Введите корректное значение!" << endl; }
    return 0;
}
