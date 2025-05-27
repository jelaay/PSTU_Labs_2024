#pragma once
#include <iostream>

using namespace std;

class Object {
public:
	Object() {}
public:
	~Object() {}
	virtual void Show() = 0;
};
