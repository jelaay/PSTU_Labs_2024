//Перегрузка функций в С++
//Постановка задачи: Написать перегруженные функции и основную программу, которая их вызывает.
//Задание: а) для сложения целых чисел; б) для сложения комплексных чисел.
#include <iostream>
#include <complex>
#include <stdio.h>

using namespace std;

int sum(int a, int b) { //для сложения целых чисел
    return a + b;
}

complex <double> sum(complex <double> a, complex <double> b) { //сложение комплексных чисел
    return a + b;
}

int summa(int count, ...) { //для 7.2 в подсчете суммы чисел.
    int sum = 0;
    int* ptr = &count;

    for (int i = 0; i < count; ++i) {
        sum += *ptr;
        ptr++;
    }
    return sum;
}

int main() {
    setlocale(LC_CTYPE, "rus");
    int n;
    cout << "Введите вариант. \n" << "1) 7.1 \n" << "2) 7.2\n";
    cin >> n;

    switch (n) {

    case(1): {

        int firstNum, secNum;
        cout << "Введите 2 числа для суммы: ";
        cin >> firstNum >> secNum;

        int resultInt = sum(firstNum, secNum); //тут сумма целых
        cout << "Целая сумма: " << resultInt << endl;

        double r1, r2, i1, i2;
        cout << "Введите числа для комплексной суммы.\n" << "(1) Действительная часть, мнимая часть: ";
        cin >> r1 >> i1;
        cout << "(2) Действительная часть, мнимая часть: ";
        cin >> r2 >> i2;
        complex <double> num1(r1, i1);
        complex <double> num2(r2, i2);
        complex <double> resultComplex = sum(num1, num2);
        cout << "Комплексная сумма: " << resultComplex.real() << " + " << resultComplex.imag() << "i" << endl;
        break;

    }
           //Написать функцию sum с переменным числом параметров, которая находит сумму чисел типа int. 
           //Написать вызывающую функцию main, которая обращается к функции sum не менее трех раз с количеством параметров 3, 7, 11.   

    case(2): {

        int result1 = summa(3, 21, 22, 32);
        int result2 = summa(7, 1, 22, 3, 43, 5, 61, 7);
        int result3 = summa(11, 1, 42, 3, 4, 45, 6, 7, 68, 9, 210, 11);

        cout << "Сумма 3 чисел: " << result1 << endl;
        cout << "Сумма 7 чисел: " << result2 << endl;
        cout << "Сумма 11 чисел: " << result3 << endl;

        break;
    }
    }

    return 0;
}


