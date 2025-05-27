#include <iostream>
#include "header.h"

using namespace std;
salaryCalculator makeCalc(double F, int S) {
    salaryCalculator temp;
    temp.Init(F, S);
    return temp;
}
int main() {
    salaryCalculator A;
    A.Init(1, 1);
    A.Read();
    A.Show();
    cout << A.summa();

    return 0;
}