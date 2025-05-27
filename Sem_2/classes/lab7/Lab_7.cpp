#include <iostream>
#include "List.h"
#include "Money.h"

using namespace std;

int main() {
	int k = 1;
	int size = 5;
	List<int> A(size);
	cout << "Result A: "; A.show();
	cout << "Result A[k]" << A[k] << endl;
	cout << "Size A: " << A() << endl;
	
	List<int> B(size);
	cout << "Result B: "; B.show();
	cout << "Size B: " << B() << endl;

	List<int> C(size);
	C = A + B;
	cout << "Result C = A + B: "; C.show();

	/////////////
	Money<long, int> a(10203040, 110);
	a.show();
	Money<long, int> b(1000000, 21);
	b.show();
	
	return 0;
}