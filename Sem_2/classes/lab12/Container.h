#pragma once

#include <list>

template<class T>

class Container
{
private:
    list<T> lst;
public:
    Container() {}
    Container(int n)
    {
        T a;
        for (int i = 0; i < n; i++)
        {
            cin >> a;
            lst.push_back(a);
        }
    }

    void Print()
    {
        for (auto it = lst.begin(); it != lst.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    T find_min()
    {
        return *min_element(lst.begin(), lst.end());
    }

    void add_at_position(int pos, T val)
    {
        auto it = lst.begin();
        advance(it, pos);
        lst.insert(it, val);
    }

    void remove_below_average()
    {
        T sum = accumulate(lst.begin(), lst.end(), T());
        T avg = sum / lst.size();

        for (auto it = lst.begin(); it != lst.end(); )
        {
            if (*it < avg) it = lst.erase(it);
            else ++it;
        }
    }

    void divide_by_max()
    {
        T max_val = *max_element(lst.begin(), lst.end());
        for (auto& elem : lst)
        {
            elem = elem / max_val;
        }
    }
};