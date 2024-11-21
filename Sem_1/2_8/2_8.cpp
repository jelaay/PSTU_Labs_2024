#include <iostream>
using namespace std;


int main()
{
    setlocale(LC_CTYPE, "rus");
    int n,stars=1;
    cout << "Введите основание треугольника, оно должно быть больше двух: ";
    cin >> n;
    if (n > 2)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= stars; j++)
            {
                cout << " *";
            }
            stars += 1;
            cout << endl;
        }
        
        
    }
    else { cout << "Введите корректное значение!" << endl; }
    return 0;
}
