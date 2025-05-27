#include "List.h"
#include <iostream>

using namespace std;

List::List(int s, int k) {
	size = s;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = k;
	}
	beg.elem = &data[0];
	end.elem = &data[size];
}

List::List(const List& a) {
	size = a.size;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = a.data[i];
	}
	beg = a.beg;
	end = a.end;
}

List::~List() {
	delete[]data;
	data = 0;
}

List& List::operator =(const List& a) {
	if (this == &a) {
		return *this;
	}
	if (data != 0) {
		delete[]data;
	}
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = a.data[i];
	}
	beg = a.beg;
	end = a.end;
	return *this;
}

int& List::operator[](int index) {
	if (index < size) {
		return data[index];
	}
	else {
		cout << "\nError (index > size)\n";
	}
}

List List::operator+(const int k) {
	List temp(size);
	for (int i = 0; i < size; i++) {
		temp.data[i] += data[i] + k;
	}
	return temp;
}

int List::operator() () {
	return size;
}

ostream& operator << (ostream& out, const List& a) {
	for (int i = 0; i < a.size; ++i) {
		cout << "OUT: " << i << " = ";
		out << a.data[i] << " ";
	}
	return out;
}

istream& operator >> (istream& in, List& a) {
	for (int i = 0; i < a.size; i++) {
		cout << "IN: " << i << " = ";
		in >> a.data[i];
	}
	return in;
}