#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

// Функция для проверки, содержит ли строка слово, начинающееся на одну букву
bool hasWordStartingWithSameLetter(const string& line) {
    if (line.empty()) return false;

    istringstream iss(line);
    string word;
    char firstLetter = '\0';

    while (iss >> word) {
        if (!word.empty()) {
            if (firstLetter == '\0') {
                firstLetter = tolower(word[0]);
            }
            else {
                if (tolower(word[0]) == firstLetter) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Функция для поиска самого короткого слова в файле
string findShortestWordInFile(const string& filename) {
    ifstream file(filename);
    string shortestWord;
    int shortestLength = INT_MAX;

    if (!file.is_open()) {
        cerr << "Не удалось открыть файл " << filename << endl;
        return "";
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            // Удаляем знаки препинания из слова (для простоты)
            if (!isalpha(word.back())) {
                word.pop_back();
            }

            if (!word.empty() && word.length() < shortestLength) {
                shortestLength = word.length();
                shortestWord = word;
            }
        }
    }

    file.close();
    return shortestWord;
}

int main() {
    setlocale(LC_CTYPE, "rus");
    // Создаем файл F1 с некоторыми строками
    ofstream f1("F1.txt");
    if (!f1.is_open()) {
        cerr << "Не удалось создать файл F1.txt" << endl;
        return 1;
    }

    f1 << "Apple and banana are fruits\n";
    f1 << "Cat dog elephant\n";
    f1 << "Hello world\n";
    f1 << "Sun moon stars\n";
    f1 << "Big black bug bit a big black bear\n"; // несколько слов на 'b'
    f1 << "Quick brown fox\n";
    f1 << "Zebra zoo\n";
    f1 << "Rain in Spain\n";
    f1 << "Peter Piper picked a peck\n"; // несколько слов на 'p'
    f1 << "Simple sample\n";
    f1 << "Just one word\n";
    f1.close();

    // Открываем F1 для чтения и F2 для записи
    ifstream input("F1.txt");
    ofstream output("F2.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Не удалось открыть один из файлов" << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) {
        // Копируем строки, которые НЕ содержат слова, начинающиеся на одну букву
        if (!hasWordStartingWithSameLetter(line)) {
            output << line << endl;
        }
    }

    input.close();
    output.close();

    // Находим самое короткое слово в F2
    string shortestWord = findShortestWordInFile("F2.txt");
    if (!shortestWord.empty()) {
        cout << "Самое короткое слово в файле F2: " << shortestWord << endl;
    }
    else {
        cout << "Файл F2 пуст или не содержит слов" << endl;
    }

    return 0;
}