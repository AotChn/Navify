#include "node.h"


bool operator ==(const node& lhs, const node& rhs){
    return lhs.i == rhs.i && lhs.j == rhs.j;
}

bool operator <(const node& lhs, const node& rhs){
    if(lhs.i < rhs.i) return true;
    if(lhs.i > rhs.i) return false;
    if(lhs.j < rhs.j) return true;  
    if(lhs.j > rhs.j) return false;  
    return false;
}

bool operator >(const node& lhs, const node& rhs){
    if(lhs.i < rhs.i) return false;
    if(lhs.i > rhs.i) return true;
    if(lhs.j < rhs.j) return false;  
    if(lhs.j > rhs.j) return true;  
    return false;
}

 bool operator <=(const node& lhs, const node& rhs){
    return lhs < rhs || lhs == rhs;
 }
 bool operator +=(const node& lhs, const node& rhs){
    return true;
 }


ostream& operator <<(ostream& outs, const node& me){
    outs << "(" << me.i << "," << me.j << ")";
    return outs;
}
