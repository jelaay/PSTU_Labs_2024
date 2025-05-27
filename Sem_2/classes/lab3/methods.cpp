#include <iostream>
#include "Header.h"

using namespace std;

Money& Money::operator =(const Money& temp) {
	if (&temp == this) {
		return *this;
	}
	rub = temp.rub;
	kop = temp.kop;
	return *this;
}

Money& Money::operator ++() {
	int temp = rub * 100 + kop;
	temp++;
	kop = temp / 100;
	kop = temp % 100;
	return *this;
}

Money Money::operator ++(int) {
	int temp = rub * 100 + kop;
	temp++;
	Money ex1(rub, kop);
	kop = temp / 100;
	kop = temp % 100;
	return ex1;
}

Money Money::operator +(const Money& temp) {
	int ex1 = rub * 100 + kop;
	int ex2 = temp.rub * 100 + temp.kop;
	Money temp2;
	temp2.rub = (ex1 + ex2) / 100;
	temp2.kop = (ex1 + ex2) % 60;
	return temp2;
}

istream& operator >>(istream& in, Money& temp) {
	cout << "rubles: ";
	in >> temp.rub;
	cout << "kopecks: ";
	in >> temp.kop;
	return in;
}

ostream& operator <<(ostream& out, const Money& temp) {
	return (out << temp.rub << ", " << temp.kop);
}