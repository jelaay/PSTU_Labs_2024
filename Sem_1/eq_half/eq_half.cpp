#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "rus");
	float a, b, c;
	float fA, fB, fC;
	double eps = 0.000001;
	a = 1;
	b = 2;
	while (b - a > eps)
	{
		c = (a + b) / 2;
		fA = (pow(a, 3) - a - 1);
		fB = (pow(b, 3) - b - 1);
		fC = (pow(c, 3) - c - 1);
		if (fA * fC < 0) { b = c; }
		else if (fC * fB < 0) { a = c; }
		else { cout << "Что-то пошло не так!" << endl; }
	}
	cout << "Корни: " << a << "; " << b << endl;
	return 0;
}
