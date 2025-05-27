#include <iostream>
#include "Error.h"
#include "List.h"

using namespace std;

int main() {
	try {
		List x(15), y;
		int i;

		cout << "Result with parametres: " << x << endl;
		cout << "Number: "; cin >> i;
		
		cout << "Result: " << x[i] << endl;

		y = x + i;

		cout << "Result y = " << y;
	}
	catch (Error e) {
		e.what();
	}
	return 0;
}