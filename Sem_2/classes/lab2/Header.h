#pragma once
#include <iostream>
#include <string>

using namespace std;
class Car {
	string model;
	string brand;
	int cost;

public:
	Car();
	Car(string, string, int);
	Car(const Car&);
	~Car();

	string getModel();
	void setModel(string);

	string getBrand();
	void setBrand(string);

	int getCost();
	void setCost(int);

	void show();
};
