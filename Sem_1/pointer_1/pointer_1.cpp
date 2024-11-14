#include <iostream>
using namespace std;

int main()
{
    int a, b,c;
    int* Aptr, * Bptr,*Cptr;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "a = " << a <<" and " << "b = " << b << endl;
    Aptr = &a;
    Bptr = &b;
    c = a;
    Cptr = &c;
    a = *Bptr;
    b = *Cptr;
    cout << "a = " << a << " and " << "b = " << b << endl;
    return 0;
}