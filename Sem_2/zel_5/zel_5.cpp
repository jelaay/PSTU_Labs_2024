#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int arr[5][5] = {
        {-45, 432, 0, 534, 364},
        {321, 643, 322, 1, 789},
        {901, 456, 453, 5, 888},
        {744, 132, 645, -56, 6},
        {636, 543, 542, 745, 9}
    };

    //вывел массив
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < 5; i++)
    {
        bool flag = false; 

        //есть ли отрицательные числа
        for (int j = 0; j < 5; j++)
        {
            if (arr[i][j] < 0)
            {
                flag = true; // нашли отрицательное число
                break;
            }
        }

        if (flag)
        {
            for (int j = 0; j < 5; j++)
            {
                arr[i][j] = 0;
            }

            for (int k = i; k < 4; k++)
            {
                for (int j = 0; j < 5; j++)
                {
                    arr[k][j] = arr[k + 1][j];
                    arr[k + 1][j] = 0;
                }
            }

            i--;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}