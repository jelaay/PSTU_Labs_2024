#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "rus");
	float x, xPrev;
	double eps = 0.000001;
	double lambda = -0.05; 
	x = 2; 
	xPrev = 0; 
	while (abs(x - xPrev) > eps)
	{
		xPrev = x;
		x = lambda * (pow(xPrev, 3) - xPrev - 1) + xPrev;
	}
	cout << "Корень по методу итераций: " << x << endl;
	return 0;
}