#pragma once
#include <iostream>

using namespace std;
const int MAX_SIZE = 20;

class List {
	int size, *beg;
public:
	List() { size = 0; beg = 0; }
	List(int L);
	List(int L, int* arr);
	List(const List&list);
	~List();

	List& operator=(const List& list);
	int operator[](int index);
	
	List operator +(const List& other);
	int operator -(int n);

	friend ostream& operator << (ostream& out, const List& list);
	friend istream& operator >> (istream& in, List& list);
};