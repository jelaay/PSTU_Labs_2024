#pragma once
#include <iostream>

using namespace std;

class Iterator {
private:
	friend class List;
	int* elem;
public:
	Iterator();
	void operator++();
	void operator--();
	int& operator *() const;
	bool operator!=(const Iterator& it);
};