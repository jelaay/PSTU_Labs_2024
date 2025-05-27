#include <iostream>
#include "List.h"
using namespace std;

int main() {
	List a(5);
	cout << a << "\n";

	cout << "Enter size A-list";
	cin >> a;
	cout << "A-list: " << a << "\n";

	a[2] = 100;
	cout << "A-list now: " << a << endl;

	List b(10);
	cout << "B-list: " << b << endl;

	b = a;
	cout << "B-list now: " << b << endl;

	List c(10);
	c = b + 100;

	cout << "C-list: " << c << endl;
	cout << "The length of A-list: " << a() << endl;

	/*****for testing*****/
	cout << *(a.first()) << endl;
	Iterator i = a.first();
	i++;
	cout << *i << endl;
	for (i = a.first(); i != a.last(); i++) {
		cout << *i << endl;
	}

	return 0;
}