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
    Graph(graph_t** picture=0, int w=0, int h=0): _grid(graph), width(w), height(h){}

    bool in_bounds(node_t id) const {
        return 0 <= id.x && id.x < width
            && 0 <= id.y && id.y < height;
    }

    bool is_blocked(node_t id) const {
        // return !walls.contains(id);
        return _grid[id.y][id.x].color < threshold;
    }

    double cost(node_t from_node, node_t to_node) const {

        return _grid[to_node.y][to_node.x].cost;
    }

    friend double heuristic(node_t a, node_t b){
        // return std::abs(a.x - b.x) + std::abs(a.y - b.y);  only move 4 Direction
        return sqrt(double(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y)));
    }

    static void set_threshold(int t);
private:
    int width, height;
    graph_t** _grid;
    static int threshold;
};

#endif