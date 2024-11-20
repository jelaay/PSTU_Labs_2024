#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n,k,z;
    cout << "Введите основание треугольника, оно должно быть нечётным и больше трёх: ";
    cin >> n;
    k = 0;
    z = 1;
    if ((n % 2 != 0) && (n > 3))
    {
        for (int i = 1; i <= ((n / 2) + 1); i++)
        {
            for (int j = 1; j <= ((n / 2)-k); j++)
            {
                cout << " ";
            }
            k += 1;
            for (int g = 1; g <= z; g++)
            {
                cout << "*";
            }
            z = z + 2;
            cout << "" << endl;
        }
    }
    else
    {
        cout << "Введите корректное значение!" << endl;
    }
    return 0;
}
