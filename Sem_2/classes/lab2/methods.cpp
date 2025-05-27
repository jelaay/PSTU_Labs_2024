//: / , 
//
//  
//
#include <iostream>
#include <string>
#include "Header.h"

using namespace std;

Car::Car() {
	model = "";
	brand = "";
	cost = 0;

	cout << "Parameterless constructor" << this << endl;
}

Car::Car(string carModel, string carBrand, int carCost) {
	model = carModel;
	brand = carBrand;
	cost = carCost;

	cout << "Constructor with parameters" << this << endl;
}

Car::Car(const Car& temp) {
	model = temp.model;
	brand = temp.brand;
	cost = temp.cost;

	cout << "opy constructor" << this << endl;
}

Car::~Car() {
	cout << "Destructor" << this << endl;
}

string Car::getModel() {
	return model;
}

string Car::getBrand() {
	return brand;
}

int Car::getCost() {
	return cost;
}

void Car::setModel(string carModel) {
	model = carModel;
}

void Car::setBrand(string carBrand) {
	brand = carBrand;
}

void Car::setCost(int carCost) {
	cost = carCost;
}

void Car::show() {
	cout << "Car model: " << model << endl;
	cout << "Car brand: " << brand << endl;
	cout << "Car cost: " << cost << endl;
}