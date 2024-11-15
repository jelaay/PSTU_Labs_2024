#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int N,sum,pr;
    cout << "Введите n: ";
    cin >> N;
    sum = 0;
    for (int i = 1; i <= N; i++)
    {
        pr = 1;
        for (int j=i;j<=i*2;j++)
        {
            pr *= j;
        }
        sum += pr;
    }
    cout << sum << endl;
    return 0;
}
