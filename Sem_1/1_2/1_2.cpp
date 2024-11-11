#include <iostream>
using namespace std;
int main()
{
	float a, b;
	cin >> a >> b;
	if ((b != 0) && (a != 0))
	{
		cout << a / b << endl;
	}
	else
		if (b == 0)
		{
			cout << "You can't divide by 0" << endl;
		}
		else
		{
			cout << 0 << endl;
		}
	return 0;
}