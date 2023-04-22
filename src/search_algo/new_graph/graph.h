#ifndef GRAPH_BUT_NEW_H
#define GRAPH_BUT_NEW_H

#include <cmath>
#include "../node/node.h"

using namespace std;

template <class graph_t, class node_t>
/*
    graph_t = a struct have 1 double cost 1 int color
    node_t  = a struct have 2 long (x, y)
*/
class Graph
{
public:
    Graph(graph_t** picture=0, int w=0, int h=0): _grid(picture), width(w), height(h){}

    bool in_bounds(node_t id) const ;
    bool is_blocked(node_t id) const ;
    bool is_valid(node_t id) const;
    double cost(node_t from_node, node_t to_node) const ;
    double heuristic(node_t a, node_t b);
    static void set_threshold(int t);
private:
    int width, height;
    graph_t** _grid;
    static int threshold;
};

#include "graph.cpp"
#endif