#include <iostream>
#include "List.h"

using namespace std;

template <class T, class T1>
class Money {
private:
	T rub;
	T kop;
public:
	Money(long, int);
	~Money();
	Money(const Money&);
	Money operator =(const Money&);
	Money operator +(const Money&);
	void show();
};

template <class T, class T1>
Money<T, T1>::Money(long R, int K) {
	rub = R;
	kop = K;
}

template <class T, class T1>
Money<T,T1>::~Money() {}

template <class T, class T1>
Money<T, T1> Money<T, T1>::operator =(const Money& money) {
	rub = money.rub;
	kop = money.kop;
}

template <class T, class T1>
void Money<T, T1>::show() {
	cout << "\nResult money: " << rub << ", " << kop;
}

template <class T, class T1>
Money<T,T1>Money<T, T1>::operator +(const Money& money) {
	int M = rub * 100 + kop;
	int monM = money.rub * 100 + money.kop;
	M += monM;

	Money temp(M / 100,  M % 100);
	return temp;
}

