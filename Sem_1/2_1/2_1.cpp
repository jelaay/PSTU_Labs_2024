#include <iostream>
using namespace std;
int main()
{
    int N, sum;
    cin >> N;
    int k = 0;
    sum = 0;
    while (k <= N)
    {
        sum += k;
        k = k + 1;
    }
    cout << sum << endl;
    return 0;
}

