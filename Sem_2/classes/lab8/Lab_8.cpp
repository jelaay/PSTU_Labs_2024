#include <iostream>
#include "Dialog.h"
using namespace std;

int main() {
	Person* p = new Person;
	p->input();
	p->show();

	Student* s = new Student;
	s->input();
	s->show();

	Tree t(10);
	Object* o = p;
	t.Add();
	o = s;
	t.Show();
	t.Del();
	cout << "\nTree: " << t() << endl;

	Dialog D;
	D.Execute();
	return 0;
}