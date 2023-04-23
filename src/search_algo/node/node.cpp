#include "node.h"


bool operator ==(const node& lhs, const node& rhs){
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator <(const node& lhs, const node& rhs){
    if(lhs.x < rhs.x) return true;
    if(lhs.x > rhs.x) return false;
    if(lhs.y < rhs.y) return true;  
    if(lhs.y > rhs.y) return false;  
    return false;
}

// bool operator >(const node& lhs, const node& rhs){
//     if(lhs.x < rhs.x) return false;
//     if(lhs.x > rhs.x) return true;
//     if(lhs.y < rhs.y) return false;  
//     if(lhs.y > rhs.y) return true;  
//     return false;
// }

 bool operator <=(const node& lhs, const node& rhs){
    return lhs < rhs || lhs == rhs;
 }
 bool operator +=(node& lhs, const node& rhs){
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return true;
 }


ostream& operator <<(ostream& outs, const node& me){
    outs << "(" << me.x << "," << me.y << ")";
    return outs;
}

node operator -(const node& lhs, const node& rhs){
    return {lhs.x -rhs.x, lhs.y - rhs.y};
}
