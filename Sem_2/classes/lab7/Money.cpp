#include <iostream>
#include "Money.h"

using namespace std;

Money::Money(void) { rub = 0; kop = 0; }
Money::Money(int R, int K) { rub = R; kop = K; }
Money::Money(const Money& m) { rub = m.rub; kop = m.kop; }
Money& Money::operator=(const Money& m) { rub = m.rub; kop = m.kop; return *this; }
Money Money::operator+(Money k) {
	int t = rub * 100 + kop;
	int kt = k.rub * 100 + k.kop;
	t += kt;
	Money temp(t / 100, t & 100);
	return temp;
}
ostream& operator << (ostream& out, const Money& t) { out << t.rub << " : " << t.kop; return out; }
istream& operator >> (istream& in, Money& t) { cout << "\nRUB: "; in >> t.rub; cout << "\nKOP: "; in >> t.kop; return in; }
