#pragma once
#include <iostream>
#include "Object.h"
#include "Person.h"
#include "Student.h"
using namespace std;

class Tree {
protected:
	Object** beg;
	int size;
	int cur;
public:
	Tree(void);
	Tree(int);
	~Tree(void);
	void Add(void);
	void Del(void);
	void Show(void);
	void Find(int);
	int operator()();
	void HandleEvent(const TEvent& event);
};
