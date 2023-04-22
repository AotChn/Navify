#ifndef A_STAR_HELPER_H
#define A_STAR_HELPER_H

#include <vector>
#include <cmath>
#include <iostream>
#include <map>

#include "bpt+/map.h"
#include "node/node.h"


using namespace std;
bool is_blocked(long graph[][COL], long x, long y){
    return graph[y][x] < thrseh_hold;
}

bool is_valid(long x, long y){
    return x >= 0 && y >= 0 && x < COL && y < ROW;
}


bool is_blocked(long graph[][COL], node x){
    return is_blocked(graph,x.i, x.j);
}

bool is_valid(node x){
    return is_valid(x.i,x.j);
}

std::vector<node> its_neighbor(const node& it){
    std::vector<node> v;
    
    v.push_back(node(it.i+1, it.j));
    v.push_back(node(it.i-1, it.j));
    v.push_back(node(it.i, it.j+1));
    v.push_back(node(it.i, it.j-1));

    return v;
}

double hueristic(const node& current, const node& goal){
    // return 	 ((double)sqrt(
	// 	(current.j - goal.j) * (current.j - goal.j)
	// 	+ (current.i - goal.i) * (current.i - goal.i)));;

    return (double) (abs(current.i - goal.i) +abs(current.j - goal.j)); 
}

void print_path(std::map<node,node> path,const node& goal){
    Map<node,node> revrse;
    auto dest = goal;
    auto src = path[goal];

    while (! (src == node()))
    {   

        revrse[src] = dest;
        dest = src;
        src = path[dest];
        /* code */
    }
    src = dest;
    while (!(src == goal))
    {      

        printf("(%d,%d)-->", src.i, src.j);
        src = revrse[src];
    }
    
    
    printf("(%d,%d)-->", src.i, src.j);
    
}


void print_path(Map<node,node> path,const node& goal){
    Map<node,node> revrse;
    auto dest = goal;
    auto src = path[goal];

    while (!(src == node()))
    {   

        revrse[src] = dest;
        dest = src;
        src = path[dest];
        /* code */
    }

    src = dest;
    while (!(src == goal))
    {      

        printf("(%d,%d)-->", src.i, src.j);
        src = revrse[src];
    }
    
    
    printf("(%d,%d)", src.i, src.j);
    
    
}


#endif