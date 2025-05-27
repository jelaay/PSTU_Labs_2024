#pragma once

#include <iostream>

using namespace std;

class Pair
{
private:
    int first;
    int second;
public:
    Pair() { first = 0; second = 0; }
    Pair(int f, int s) { first = f; second = s; }
    Pair(const Pair& p) { first = p.first; second = p.second; }

    int get_first() const { return first; }
    int get_second() const { return second; }
    void set_first(int f) { first = f; }
    void set_second(int s) { second = s; }

    Pair operator+(const Pair&);
    Pair operator-(const Pair&);
    Pair operator/(const Pair&);
    Pair operator/(const int);
    bool operator<(const Pair&) const;
    bool operator>(const Pair&) const;
    friend istream& operator>>(istream& in, Pair& p);
    friend ostream& operator<<(ostream& out, const Pair& p);
};