#include <iostream>
using namespace std;

int main()
{
	int a, b, answ;
	int* aptr;
	int* bptr;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	aptr = &a;
	bptr = &b;
	answ = *aptr + *bptr;
	cout << *aptr << " + " << *bptr << " = " << answ << endl;
	return 0;
}
