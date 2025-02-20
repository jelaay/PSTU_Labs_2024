#include <iostream>
using namespace std;
/*
//функция проверки наличия фрезей на вертикале, если true - то свободно
bool vertical(n)
{
    int v = n;
    bool answ = true;
    for (int j = 0; j < 8; j++)
    {
        if (arr[v][j] != 0)
        {
            answ = false;
            break;
        }
    }
    return answ;
}

//функция првоерки наличия фрезей на горизонтале, если true - то свободно
bool horizontal(n)
{
    int h = n;
    bool answ = true;
    for (int i = 0; i < 8; i++)
    {
        if (arr[i][h] != 0)
        {
            answ = false;
            break;
        }
    }
    return answ;
}

bool diagonal(n)
{
    int g = n;
    bool answ = true;
    for (int i = 0; i < 8; i++)
    {
        if (arr[i][i] != 0)
        {
            answ = false;
            break;
        }
    }
    return answ;
}*/

int main()
{
    int arr[8][8] = { 0 }; //создали массив, состоящий из 0, где 0 - пустая (не занятая ферзём) клетка
    int q = 0;

    for (int i = 0; i < 8; i++) //вывел массив (доску)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << arr[i][j]<<" ";
        }   
        cout << endl;
    }

    /*
    while (q < 8)
    {
        for (int i = 0; i < 8; i++) // идем по столбцам
        {
            if (vertical(i) == true)
            {
                for (int j = 0; j < 8; j++) //идём по строкам
                {
                    if (horizontal(j) == true)
                    {
                        for (int g = 0; g < 8; g++) //проверяем диагональ
                        {
                            if (diagonal(g) == true)
                            {
                                arr[g][g] = 1;
                                break;

                            }
                        }
                    }
                }
            }

        }
    }
    for (int i = 0; i < 8; i++) //вывел массив (доску)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }*/
    return 0;
}
