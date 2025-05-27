#include <iostream>
#include "header.h"

using namespace std;

void salaryCalculator::Init(double F, int S) {
    first = F;
    second = S;
}

void salaryCalculator::Read() {
    cout << "Salary: ";
    cin >> first;
    cout << "Days: ";
    cin >> second;
}

void salaryCalculator::Show() {
    cout << "Salary = " << first << endl;
    cout << "Days = " << second << endl;
}

double salaryCalculator::summa() {
    return (first * second) / 30;
}