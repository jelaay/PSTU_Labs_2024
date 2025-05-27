#pragma once
#include <iostream>
#include "Event.h"

using namespace std;

class Object {
public:
	 virtual void show() = 0;
	 virtual void input() = 0;
	 void HandleEvent(const TEvent&);
};