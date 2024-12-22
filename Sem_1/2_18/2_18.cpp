#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int n, r;
    cin >> n;
    r = 0;
    while (n > 0)
    {
        r = r * 10 + n % 10;
        n /= 10;
    }
    cout << r << endl;
    return 0;
}