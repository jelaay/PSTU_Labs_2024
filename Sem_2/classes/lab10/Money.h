#pragma once
#include <iostream>
#include <fstream>

using namespace std;
class Money {
private:
	long rub;
	int kop;
public: 
	~Money();
public:
	Money();
	Money(long, int);	
	Money(const Money&);
	Money operator =(const Money&);
	Money operator +(const Money&);
	bool operator ==(int val);
	void show();

	friend istream& operator >>(istream& in, Money& money);
	friend ostream& operator <<(ostream& out, const Money& money);
	
	friend fstream& operator >> (fstream& fin, Money& money);
	friend fstream& operator << (fstream& fout, const Money& money);
};