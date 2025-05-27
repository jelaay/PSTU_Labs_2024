//money
//long - rub, int - kop
//cpaenewe добавление копеек
#include <iostream>
#include "Header.h"

using namespace std;

int main() {
    Money A, B, C;
    cin >> A >> B;
    ++A;

    cout << A << endl;
    C = (A++) + B;

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    return 0;
}