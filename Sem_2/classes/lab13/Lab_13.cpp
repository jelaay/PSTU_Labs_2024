#include <iostream>
#include "Methods_1.h"
#include "Methods_2.h"

using namespace std;

int main() {
	srand(time(0));
	try {

		vector<Money> v;
		int size;
		cout << "Enter size (vector): "; cin >> size;
		v = makeVector(size);
		cout << "Vector (money): "; printVector(v);

		Money a(average(v), 0);
		v.insert(v.begin(), a);
		cout << "Result: "; printVector(v);

		int elem;
		cout << "Element to delete: "; cin >> elem;
		//v.erase(remove(v.begin(), v.end(), elem), v.end()); //del 
		printVector(v);

		cout << "Vector - min Element" << endl;
		minElem(v);
		cout << endl;

		Money mm;
		q que;
		int sizeq;
		cout << "Enter size (queue): "; cin >> sizeq;
		que = makeQueue(sizeq);
		printQueue(que);
		averageQ(que);
		int index;
		cout << "Index: "; cin >> index;
		addQueue(que, mm, index);
		cout << "Add elem: "; printQueue(que);
		cout << endl;

		minElem(que);
		cout << "Result: "; printQueue(que);
		cout << endl;
	}
	catch (int) { cout << "Error" << endl;}

	return 0;
}