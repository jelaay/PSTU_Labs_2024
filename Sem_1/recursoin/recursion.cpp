/*
* 1. Вести данные
* 2. НОК=(a*b)/НОД(a,b)
* 3. НОД(по алгоритму евклида)=max-min(до тех пор, пока max=min)
* Ограничения: числа долбны быть >0
*/
#include <iostream>
using namespace std;

int nod(int a, int b)
{
	int max, min;
	if (a == b) {return a; }
	else if (a > b) 
	{
		max = a-b;
		min = b; 
		nod(max, min);
	}
	else  
	{
		max = b-a;
		min = a;
		nod(max, min);
	}
	
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	int a, b,res;
	cout << "Введите первое натуральное число: ";
	cin >> a;
	cout << "Введите второе натуральное число: ";
	cin >> b;
	res = 0;
	if ((a > 0) && (b > 0))
	{
		res = nod(a, b);
		cout << "НОК двух натуральных чисел " << a << " и " << b << " = " << (a * b) / res << endl;
	}
	else { cout << "Необходимо ввести целые числа, большие нуля!" << endl; }
	return 0;
}