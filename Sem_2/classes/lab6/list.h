#pragma once
#include <iostream>

using namespace std;

class List {
public:
	List(int s, int k = 0);
	List(const List& a);
	~List();
	List& operator =(const List& a);
	int& operator[] (int index);
	List operator +(const int k);
	int operator()();

	friend ostream& operator <<(ostream& out, const List&);
	friend istream& operator >> (istream& in, List& a);

	Iterator first() { return beg; }
	Iterator last() { return end; }

private:
	int size;
	int* data;
	Iterator beg, end;
};

