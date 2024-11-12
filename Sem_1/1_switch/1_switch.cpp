#include <iostream>
using namespace std;

int main()
{
    float a, b;
    int op;
    cout << "first, second, 1 - summ, 2 - vich, 3 - umn, 4 - del"<<endl;
    cin >> a >> b >> op;
    switch (op)
    {
    case 1: cout << a + b << endl; break;
    case 2: cout << a - b << endl; break;
    case 3: cout << a * b << endl; break;
    case 4: 
    {
        if ((b != 0) && (a != 0))
        {
            cout << a / b << endl;
        }
        else
            if (b == 0)
            {
                cout << "You can't divide by 0" << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        break;
    }
    default: cout << "wrong znach" << endl;
    }
    return 0;
}

