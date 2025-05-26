#include <iostream>

using namespace std;
int* prefixFunc(string pat, int size) {
    int* lps = new int[size];
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < size) {
        if (pat[i] == pat[len]) {
            lps[i] = len;
            len++;
            i++;
        }
        else {
            if (len != 0) { len = lps[len - 1]; }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KnuthMorrisPatt(string str, string pat) {
    int str_size = str.size(), pat_size = pat.size(), str_idx = 0, pat_idx = 0;
    int* lps = prefixFunc(pat, pat_size);

    while ((str_size - str_idx) >= (pat_size - pat_idx)) {
        if (pat[pat_idx] == str[str_idx]) {
            str_idx++;
            pat_idx++;
        }
        if (pat_idx == pat_size) {
            cout << "Индекс: " << (str_idx - pat_idx) + 1 << endl;
            pat_idx = lps[pat_idx - 1];
        }
        else if (str_idx < str_size && pat[pat_idx] != str[str_idx]) {
            if (pat_idx != 0) {
                pat_idx = lps[pat_idx - 1];
            }
            else { str_idx++; }
        }
    }

}

int main() {
    setlocale(LC_CTYPE, "rus");
    char str[100];
    char pat[100];
    cout << "Введите строку: ";
    cin >> str;

    cout << "Введите образец: ";
    cin >> pat;

    cout << "Рузультат поиска Кнут-Моррис-Прат: ";
    KnuthMorrisPatt(str, pat);
    return 0;
}