#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "..\constants.h"


using namespace std;

struct node
{   
    long x, y;
    friend bool operator <(const node& lhs, const node& rhs);
    friend bool  operator ==(const node& lhs, const node& rhs);

    friend bool operator <=(const node& lhs, const node& rhs);
    friend bool operator +=(const node& lhs, const node& rhs);
    friend ostream& operator <<(ostream& outs, const node& me);

    friend node operator -(const node& lhs, const node& rhs);
};


#endif