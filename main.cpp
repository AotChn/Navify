#include <iostream>
#include "src\search_algo\a_star.h"
using namespace std;

// comment


int main(){
    cout << "\n\n\n"
        << "==============Entering Main=================\n\n\n";
    
    long graph[ROW][COL] =
    {
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,0,1,1,1,1,1},
        {1,1,1,1,0,1,1,1,1,1},
        {0,0,0,0,0,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
    };

    node start(0,0);
    node end(5,5);

    cout << "is_blocked(start)?" << is_blocked(graph, start) << endl;
    cout << "is_blocked(end)?" << is_blocked(graph, end) << endl;
    cout << "is_valid(start)?" << is_valid(start) << endl;
    cout << "is_valid(end)?" << is_valid(end) << endl;

    a_star(graph, start,end);
    
    cout << "\n\n\n"
        << "==============Leaving Main==================\n\n\n";
    return  0;
}
