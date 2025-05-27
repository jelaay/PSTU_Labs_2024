#pragma once
#include <iostream>
#include <string>

using namespace std; 

class Error {
	string str;
public: 
	Error(string S) { str = S; }
	void what() { cout << str << endl; }
};