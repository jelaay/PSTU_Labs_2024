#include <iostream>
#include <string>
#include "Header.h"

using namespace std;

Car enterCar() {
	string modelCar;
	string brandCar;
	unsigned int costCar;

	cout << "What model?";
	cin >> modelCar;

	cout << "What brand?";
	cin >> brandCar;

	cout << "What price?";
	cin >> costCar;

	Car temp(modelCar, brandCar, costCar);
	return temp;
}

void showCar(Car temp) {
	temp.show();
}

int main() {
	Car ex1;
	ex1.show();

	Car ex2("Lada", "Lada Vesta", 1500000);
	ex2.show();

	Car ex3 = ex2;
	ex3.setBrand("Infiniti");
	ex3.setModel("Infiniti QX 50");
	ex3.setCost(2500000);

	showCar(ex3);

	ex1 = enterCar();
	ex1.show();

	return 0;
}