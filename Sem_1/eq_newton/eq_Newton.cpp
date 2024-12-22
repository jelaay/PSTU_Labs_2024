#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "rus");
	float x, xPrev; 
	x = 2; 
	xPrev = 0; 
	double eps = 0.000001;
	while (abs(x - xPrev) > eps)
	{
		xPrev = x;
		x = xPrev - ((pow(xPrev, 3) - xPrev - 1) / (3 * pow(xPrev, 2) - 1));
	}
	cout << "Корень: " << x << endl;
	return 0;
}