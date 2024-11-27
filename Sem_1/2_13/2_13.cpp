#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    float a, b, c,answ1,answ2,d;
    cout << "Для решения квадратного уравнения вида: a * x^2 + b*x + c = 0, введите:" << endl;
    cout << "Коэфицент а: ";
    cin >> a;
    cout << "Коэфицент b: ";
    cin >> b;
    cout << "Коэфицент c: ";
    cin >> c;
    d = (b * b) - (4 * a * c);
    if (d > 0)
    {
        answ1 = ((-b) + sqrt(d)) / 2 * a;
        answ2 = ((-b) - sqrt(d)) / 2 * a;
        cout << "Первый корень уравнения: " << answ1 << endl;
        cout << "Второй корень уравнения: " << answ2 << endl;
    }
    else if (d < 0) { cout << "Дискриминант меньше 0. Корней нет." << endl; }
    else
    {
        answ1 = (-b) / 2 * a;
        cout << "Два совпадающих корня уравнения : " << answ1 << endl;
    }
    return 0;
}
