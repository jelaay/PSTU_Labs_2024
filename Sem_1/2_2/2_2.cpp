#include <iostream>
using namespace std;

int main()
{
    int prod, N;
    int k = 1;
    cin >> N;
    prod = 1;
    while (k <= N)
    {
        prod = prod * k;
        k = k + 1;
    }
    cout << prod << endl;
    return 0;
}
