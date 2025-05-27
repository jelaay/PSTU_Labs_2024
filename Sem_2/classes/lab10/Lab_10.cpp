#include "Money.h"
#include <iostream>
#include <fstream>
#include "File.h"

using namespace std;

int main() {
	Money A; cin >> A;
	cout << "A:  " << A << endl;

	Money B; B = A;
	cout << endl;
	cout << "B: " << B << endl;

	cout << "\n****************FILE****************" << endl;
	Money M;
	int tmp, choise;
	char fileName[30];

	do {
		cout << "\n1. Make file";
		cout << "\n2. Print file";
		cout << "\n3. Delete record from file";
		cout << "\n4. Add record to file";
		cout << "\n5. Change record in file";
		cout << "\n0. Exit\n";
		cin >> choise;
		switch (choise) {
		case 1:
			cout << "File name: "; cin >> fileName;
			tmp = makeFile(fileName);
			if (tmp < 0) { cout << "Can't make file" << endl; }
			break;
		case 2: 
			cout << "File name: "; cin >> fileName;
			tmp = makeFile(fileName);
			if (tmp == 0) { cout << "Empty file\n"; }
			if (tmp < 0) { cout << "Can't read file\n"; }
			break;
		case 3:
			cout << "File name: "; cin >> fileName;
			int num; cout << "Number: "; cin >> num;
			tmp = delFile(fileName, num);
			if (tmp < 0) { cout << "Can't read file" << endl; }
			break;
		case 4: {
			Money m1;
			cout << "File name: "; cin >> fileName;
			cout << "Number: "; cin >> num;
			cout << "New money sum: "; cin >> m1;
			tmp = addFile(fileName, num, m1);
			if (tmp < 0) { cout << "Can't read file" << endl; }
			if (tmp == 0) { tmp = addEnd(fileName, m1); }
			break; 
		}	
		case 5: {
			Money m2;
			cout << "File name: "; cin >> fileName;
			cout << "\nNumber: "; cin >> num;
			cout << "\nNew money sum: "; cin >> m2;
			tmp = changeFile(fileName, m2, num);
			if (tmp < 0) { cout << "Can't read file" << endl; }
			if (tmp == 0) { cout << "\nNot such record" << endl; }
			break;
			}
		}
	} while (choise != 0);
	return 0;
}