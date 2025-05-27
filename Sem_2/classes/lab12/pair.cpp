#include "Pair.h"

Pair Pair::operator+(const Pair& p)
{
    int f = first + p.first;
    int s = second + p.second;
    f += s / 100;
    s = s % 100;
    return Pair(f, s);
}

Pair Pair::operator-(const Pair& p)
{
    int f = first - p.first;
    int s = second - p.second;
    return Pair(f, s);
}

Pair Pair::operator/(const Pair& p)
{
    int total1 = first * 100 + second;
    int total2 = p.first * 100 + p.second;
    return Pair(0, total1 / total2);
}

Pair Pair::operator/(const int n)
{
    int total = first * 100 + second;
    total /= n;
    return Pair(total / 100, total % 100);
}

bool Pair::operator<(const Pair& p) const
{
    int total1 = first * 100 + second;
    int total2 = p.first * 100 + p.second;
    return total1 < total2;
}

bool Pair::operator>(const Pair& p) const
{
    int total1 = first * 100 + second;
    int total2 = p.first * 100 + p.second;
    return total1 > total2;
}

istream& operator>>(istream& in, Pair& p)
{
    cout << "First: "; in >> p.first;
    cout << "Second: "; in >> p.second;
    return in;
}

ostream& operator<<(ostream& out, const Pair& p)
{
    out << '(' << p.first << "," << p.second << ')';
    return out;
}