#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int main() 
{
    setlocale(LC_CTYPE, "rus");
    char s[256];
    cout << "Введите строку: ";
    cin.getline(s, 256);

    cout << "Палиндромы: ";

    char* word = strtok(s, " ,.!?;:-");
    while (word != NULL)
    {
        bool isPal = true;
        int len = (int)strlen(word);
        for (int i = 0; i < len / 2; i++)
        {
            if (tolower(word[i]) != tolower(word[len - 1 - i]))
            {
                isPal = false;
                break;
            }
        }
        if (isPal && len > 0)
        {
            cout << word << " ";
        }
        word = strtok(NULL, " ,.!?;:-");
    }
    return 0;
}