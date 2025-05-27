#include "Person.h"
#include <iostream>

using namespace std;

Person::Person(void) {
	name = " ";
	age = 0;
}

Person::Person(string N, int A) {
	name = N;
	age = A;
}

Person::Person(const Person& person) {
	name = person.name;
	age = person.age;
}

Person::~Person(void) {}

string Person::get_name() { return name;}

int Person::get_age() { return age; }

void Person::set_name(string N) {name = N;}

void Person::set_age(int A) {age = A;}

Person& Person::operator=(const Person& person) {
	if (&person == this) { return *this; }
	name = person.name;
	age = person.age;
	return *this;
}

void Person::show() {
	cout << "\nPerson name: " << name << endl;
	cout << "\nPerson age: " << age << endl;
}

void Person::input() {
	cout << "\nEnter name: "; cin >> name;
	cout << "\nEnter age: "; cin >> age;
}