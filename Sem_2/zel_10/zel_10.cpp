#include <iostream>

using namespace std;

int main() 
{
    setlocale(LC_CTYPE, "rus");
    int rows, cols;
    cout << "Введите размеры массива (строки столбцы): ";
    cin >> rows >> cols;

    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) 
        {
            arr[i][j] = i * cols + j + 1;
        }
    }

    cout << "Исходный массив:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) 
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    int delRow, delCol;
    cout << "Какую строку удалить?";
    cin >> delRow;
    cout << "Какой столбец удалить?";
    cin >> delCol;

    int newRows = rows - 1;
    int newCols = cols - 1;
    int** newArr = new int* [newRows];
    for (int i = 0; i < newRows; i++) 
    {
        newArr[i] = new int[newCols];
    }

    int new_i = 0;
    for (int i = 0; i < rows; i++)
    {
        if (i == delRow) continue;

        int new_j = 0;
        for (int j = 0; j < cols; j++)
        {
            if (j == delCol) continue;

            newArr[new_i][new_j] = arr[i][j];
            new_j++;
        }
        new_i++;
    }

    cout << "Массив после удаления:\n";
    for (int i = 0; i < newRows; i++) 
    {
        for (int j = 0; j < newCols; j++) 
        {
            cout << newArr[i][j] << " ";
        }
        cout << endl;
    }


    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    for (int i = 0; i < newRows; i++) {
        delete[] newArr[i];
    }
    delete[] newArr;

    return 0;
}