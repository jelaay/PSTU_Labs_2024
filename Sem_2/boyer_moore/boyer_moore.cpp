#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int CHAR_NUM = 256;

void calcTable(char* str, int size, int charTable[CHAR_NUM]) {
    for (int i = 0; i < CHAR_NUM; i++) {
        charTable[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        charTable[str[i]] = i;
    }
}

void BoyerMoore(char* str, char* pat) {
    int patSize = strlen(pat);
    int strSize = strlen(str);

    int shiftChar[CHAR_NUM];

    calcTable(pat, patSize, shiftChar);
    bool isFound = false;
    int shift = 0;

    while (shift <= (strSize - patSize)) {
        int endPat = patSize - 1;

        while (endPat >= 0 && pat[endPat] == str[shift + endPat]) {
            endPat--;
        }

        if (endPat < 0) {
            cout << "Образец найден по индексу: " << shift << endl;
            shift += (shift + patSize < strSize) ? patSize - shiftChar[str[shift + patSize]] : 1;
            isFound = true;

        }
        else {
            shift += max(1, endPat - shiftChar[str[shift + endPat]]);
        }
        if (!isFound) {
            cout << "Не найдено" << endl;
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    char str[100];
    char pat[100];
    cout << "Введите строку: ";
    cin >> str;

    cout << "Введите шаблон: ";
    cin >> pat;

    cout << "Результат поиска Бойер-Мур: ";
    BoyerMoore(str, pat);
    return 0;
}

