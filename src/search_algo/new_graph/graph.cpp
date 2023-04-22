#ifndef NEW_GRAPH_CPP
#define NEW_GRAPH_CPP
#include "graph.h"


template <class graph_t, class node_t>
int Graph<graph_t, node_t>::threshold;

template <class graph_t, class node_t>
void Graph<graph_t, node_t>::set_threshold(int t){
    threshold = t;
}

template <class graph_t, class node_t>
bool Graph<graph_t, node_t>::in_bounds(node_t id) const {
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
}

template <class graph_t, class node_t>
bool Graph<graph_t, node_t>::is_blocked(node_t id) const {
    // return !walls.contains(id);
    assert(_grid);
    return _grid[id.y][id.x].color < threshold;
}
template <class graph_t, class node_t>
bool Graph<graph_t, node_t>::is_valid(node_t id) const{
    return in_bounds(id) &&  !is_blocked(id) ;
}

template <class graph_t, class node_t>
double Graph<graph_t, node_t>::cost(node_t from_node, node_t to_node) const {
    assert(_grid);
    return _grid[to_node.y][to_node.x].cost;
}

template <class graph_t, class node_t>
double Graph<graph_t, node_t>::heuristic(node_t a, node_t b){
    // return std::abs(a.x - b.x) + std::abs(a.y - b.y);  only move 4 Direction
    return sqrt(double(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y)));
}

#endif