#include <iostream>
using namespace std;

int arr[8][8] = { 0 }; // Глобальная переменная, как у вас было

// Проверка вертикали и горизонтали
bool safe(int row, int col) 
{
    // Проверяем вертикаль (столбец)
    for (int i = 0; i < 8; i++) 
    {
        if (arr[i][col] != 0) return false;
    }

    // Проверяем горизонталь (строка)
    for (int j = 0; j < 8; j++) 
    {
        if (arr[row][j] != 0) return false;
    }

    // Проверяем диагонали
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) 
    {
        if (arr[i][j] != 0) return false;
    }

    for (int i = row, j = col; i < 8 && j >= 0; i++, j--) 
    {
        if (arr[i][j] != 0) return false;
    }

    for (int i = row, j = col; i >= 0 && j < 8; i--, j++) 
    {
        if (arr[i][j] != 0) return false;
    }

    for (int i = row, j = col; i < 8 && j < 8; i++, j++) 
    {
        if (arr[i][j] != 0) return false;
    }

    return true;
}

bool queenPos(int col) 
{
    if (col >= 8)
    {
        return true;
    }

    for (int i = 0; i < 8; i++) {
        if (safe(i, col)) {
            arr[i][col] = 1;
            if (queenPos(col + 1))
            {
                return true;
            }
            arr[i][col] = 0; 
        }
    }
    return false;
}

int main() {
    if (queenPos(0)) {
        // Выводим доску
        for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++) 
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Решение не найдено" << endl;
    }

    return 0;
}