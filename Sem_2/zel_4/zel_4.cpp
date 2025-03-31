#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int tmp;
    const int n = 10;
    int arr[n];
    int range_min, range_max;
    range_min = 2;
    range_max = 412;
    //создали случайный массив, распечатали
    cout << "Исходный массив" << endl;
    for (int i = 0; i < n;i++)
    {
        arr[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
        cout << arr[i] << " ";
    }
    cout << endl;

    //удалили первые 5 элепментов массива
    for (int i = 0;i < 5;i++)
    {
        arr[i] = arr[i + 5];
    }
    cout << "Удалили первые 5 элементов" << endl;
    for (int i = 0;i < 5;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Конечный массив" << endl;
    for (int i = 5; i < 8;i++)
    {
        arr[i] = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    }

    for (int i = 0;i < 8;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
