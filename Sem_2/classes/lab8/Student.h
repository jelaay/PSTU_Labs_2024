#pragma once
#include <iostream>
#include "Person.h"
#include <string>

using namespace std;

class Student : public Person {
protected: 
	float rating;
public:
	Student(void);
	Student(string name, int age, float rating);
	Student(const Student& s);
	~Student(void);
	float get_rating() { return rating; }
	void set_rating(float rating);
	void show();
	void input();
	Student& operator=(const Student&);
};
