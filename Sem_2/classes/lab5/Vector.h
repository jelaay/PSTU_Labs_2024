#pragma once
#include <iostream>
#include "Object.h"

using namespace std;

class Vector {
public:
	Vector(void);
	Vector(int);
public:
	~Vector(void);
	void Add(Object*);
	friend ostream& operator <<(ostream& out, const Vector&);
private:
	Object** ptr;
	int size, cur;
};