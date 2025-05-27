#include "Triad.h"
#include "Object.h"
#include <iostream>
#include "Time.h"
#include "Vector.h"

using namespace std;

int main() {
	Triad example;

	cin >> example;
	cout << example << endl;

	Object* p = &example;
	p->Show();

	Time example2;

	cin >> example2;
	cout << example2 << endl;

	p = &example2;
	p->Show();

	Vector v(5);
	Triad a;
	Time b;

	cin >> a >> b;

	p = &a;
	v.Add(p);
	p = &b;
	v.Add(p);

	cout << v;

	return 0;
}