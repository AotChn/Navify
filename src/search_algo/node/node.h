#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include "..\constants.h"
using namespace std;
struct node
{   
    //In cartitian coordinate: x = i, y = j;
    node(long _i = -1, long _j = -1, double _f = 10000000): i(_i),j(_j),f(_f){}
    long i, j;
    double f, g, h;
    friend bool operator ==(const node& lhs, const node& rhs);
    friend bool operator <(const node& lhs, const node& rhs);
    friend bool operator >(const node& lhs, const node& rhs);
    friend bool operator <=(const node& lhs, const node& rhs);
    friend bool operator +=(const node& lhs, const node& rhs);

    friend ostream& operator <<(ostream& outs, const node& me);
};


#endif