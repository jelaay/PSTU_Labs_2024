#include <iostream>
using namespace std;

void towerOh(int disks, char start, char end, char tmp) 
 {
    if (disks == 1) 
    {
        cout << "Переместить диск 1 с " << start << " на " << end << endl;
        return;
    }
    towerOh(disks - 1, start, tmp, end);
    cout << "Переместить диск " << disks << " с " << start << " на " << end << endl;
    towerOh(disks - 1, tmp, end, start);
}


int main() 
{
    setlocale(LC_ALL, "rus");
    int disks = 3; 
    towerOh(disks, 'A', 'C', 'B'); // A - начальный стержень (start), C - конечный(end), B - вспомогательный(tmp)
    return 0;
}