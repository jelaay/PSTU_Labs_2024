#include <iostream>
#include "Header.h"
#include "Time.h"

using namespace std;

void f1(Triad& triad) {
    triad.setFirst(111);
    triad.setSecond(222);
    triad.setThird(333);
    cout << triad;
}

Triad f2() {
    Time time(0, 0, 0);  // Убраны лишние нули
    return time;
}

int main() {
    Triad num0;
    cin >> num0;
    cout << num0;

    Triad num1(0, 11, 22);
    cout << num1;

    num0 = num1;
    cout << num0;

    Time time;
    cin >> time;
    cout << time;

    return 0;
}