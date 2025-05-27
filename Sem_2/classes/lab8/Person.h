#pragma once
#include <iostream>
#include "Object.h"
#include <String>

using namespace std;

class Person : public Object {
protected:
	string name;
	int age;
public: 
	Person(void);
	Person(string name, int age);
	Person(const Person& p);
	~Person(void);
	string get_name();
	int get_age();
	void set_name(string name);
	void set_age(int age);
	Person& operator =(const Person& p);
	void show();
	void input();
};