#include "edge.h"

EDGE::EDGE()
{
}

EDGE::EDGE(int X_from, int Y_from, int X_to, int Y_to, int Weight, int Type)
{
    x_from = X_from;
    y_from = Y_from;
    x_to = X_to;
    y_to = Y_to;
    weight = Weight;
    type = Type;
}
