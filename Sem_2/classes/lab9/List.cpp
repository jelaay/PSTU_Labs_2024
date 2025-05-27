#include "List.h"
#include <iostream>
#include "Error.h"


using namespace std;

List::List(int l) {
	size = l;
	beg = new int[l];
	for (int i = 0; i < size; i++) { beg[i] = 1; }
}

List::List(int l, int* arr) {
	if (l > MAX_SIZE) throw Error("Length > 20\n");
	size = l;
	beg = new int[size];
	for (int i = 0; i < size; i++) { beg[i] = arr[i]; }
}
List::List(const List& list) {
	size = list.size;
	beg = new int[size];
	for (int i = 0; i < size; i++) {
		beg[i] = list.beg[i];
	}
}

List::~List() { 
	if (beg != 0) { delete[] beg; } 
}

List& List::operator=(const List& list) {
	if (this == &list) { return *this; }
	if (beg != 0) { delete[]beg; }
	size = list.size;
	beg = new int[size];
	for (int i = 0; i < size; i++) { beg[i] = list.beg[i]; }
	return *this;
}

int List::operator[] (int index) {
	if (index > size) { throw Error("index > size"); }
	if (index < 0) { throw Error("Index < 0 or > size"); }
	return beg[index];
}

List List::operator +(const List&other) {
	List result;
	if (size != other.size) {return result;}
	result.size = size;
	result.beg = new int[size];
	for (int i = 0; i < size; i++) {result.beg[i] = beg[i] + other.beg[i];}
	return result;
}
int List::operator-(int n) {
	if (n >= 0 && n < size) {return beg[n];}
	else { throw Error("Error n"); }
}
ostream& operator << (ostream& out, const List& list) {
	if (list.size == 0) { out << "Empty" << endl; }
	else {
		for (int i = 0; i < list.size; i++) { out << list.beg[i] << " "; }
		out << endl;
	}
	return out;
}
istream& operator >> (istream& in, List& list) {
	for (int i = 0; i < list.size; i++) {
		cout << " > ";
		in >> list.beg[i];
	}
	return in;
}

