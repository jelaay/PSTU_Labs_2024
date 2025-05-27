#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Money.h"

using namespace std;

int makeFile(const char* fileName) {
	fstream file(fileName, ios::out | ios::trunc);
	if (!file) { return -1; }
	int n;
	Money m1;
	cout << "\nEnter count: "; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> m1;
		file << m1 << "\n";
	}
	file.close();
	return n;
}

int printFile(const char* fileName) {
	fstream file(fileName, ios::in);
	if (!file) { return -1; }
	Money m2; int i = 0;
	while (file >> m2) {
		cout << m2 << "\n";
		i++;
	}
	file.close();
	return i;
}

int delFile(const char* fileName, int index) {
	fstream temp("temp", ios::out);
	fstream file(fileName, ios::in);
	if (!file) { return -1; }
	int i = 0; Money m3;
	while (file >> m3){
		if (file.eof()) { break; }
		i++;
	if (i!= index) { temp << m3; }
	}
	file.close(); temp.close();
	remove(fileName);
	rename("temp", fileName);
	return i;
}

int addFile(const char* fileName, int index, Money m) {
	fstream temp("temp", ios::out);
	fstream file(fileName,ios::in);
	if (!file) { return -1; }
	Money m4; int i = 0, l = 0; 
	while (file >> m4) {
		if (file.eof()) { break; }
		i++;
		if (i == index) {
			temp << m4;
			l++;
		}
		temp << m4;
	}
	file.close(); temp.close(); 
	remove(fileName); 
	rename("temp", fileName);
	return l;
}

int addEnd(const char* fileName, Money m) {
	fstream file(fileName, ios::app);
	if (!file) { return -1; }
	file << m; 
	return 1;
}

int changeFile(const char* fileName, Money m, int index) {
	fstream temp("temp", ios::out);
	fstream file(fileName, ios::in);
	if (!file) { return -1; }
	Money m5; int i = 0, l = 0; char x; 
	while (file >> m5) {
		if (file.eof()) { break; }
		i++;
		if (i == index) {
			cout << m5 << " - is changing... Continue[y/n]?\n"; cin >> x;
			if (x == 'n' || x == 'N')break; 
			temp << m;
			l++;
		}
		else temp << m5;
	}
	file.close(); temp.close(); 
	remove(fileName); 
	rename("temp", fileName);
	return l;
}