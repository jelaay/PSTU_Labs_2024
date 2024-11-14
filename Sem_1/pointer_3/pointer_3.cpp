#include <iostream>
using namespace std;

int main()
{
    float a, b,answ;
    float *aptr;
    float *bptr;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    aptr = &a;
    bptr = &b;
    answ = *aptr + *bptr;
    cout << *aptr << " + " << *bptr << " = " << *aptr + *bptr;
    return 0;
}
