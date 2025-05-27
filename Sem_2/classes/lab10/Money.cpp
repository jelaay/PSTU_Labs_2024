#include "Money.h"
#include <iostream>
#include <fstream>

using namespace std;

Money::Money() {
	rub = 20;
	kop = 21;
}
Money::Money(long R, int K) {
	rub = R;
	kop = K;
}
Money::~Money() {}

Money::Money(const Money& money) {
	rub = money.rub;
	kop = money.kop;
}

Money Money::operator =(const Money& money) {
	if (&money == this) { return *this; }
	rub = money.rub;
	kop = money.kop;
	return *this;
}
istream& operator >>(istream& in, Money& money) {
	cout << "\nEnter RUB: " << money.rub;
	cout << "\nEnter KOP: " << money.kop;
	cout << endl;
	return in;
}

ostream& operator <<(ostream& out, const Money& money) {
	out << "\nrub: " << money.rub;
	out << "\nkop: " << money.kop;
	cout << endl;
	return out;
}

fstream& operator >> (fstream& fin, Money& m) {
	fin >> m.rub;
	fin >> m.kop;
	return fin;
}
fstream& operator << (fstream& fout, const Money& m) {
	fout << m.rub << "\n" << m.kop << "\n";
	return fout;
}


void Money::show() {
	cout << "\nResult money: " << rub << ", " << kop;
}

Money Money::operator +(const Money& money) {
	int M = rub * 100 + kop;
	int monM = money.rub * 100 + money.kop;
	M += monM;

	Money temp(M / 100, M % 100);
	return temp;
}
bool Money::operator==(int val) {
	int all = rub * 100 + kop;
	return all == val;
}