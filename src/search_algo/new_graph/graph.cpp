#include "graph.h"


template <class graph_t, class node_t>
int Graph<graph_t, node_t>::threshold;

template <class graph_t, class node_t>
void Graph<graph_t, node_t>::set_threshold(int t){
    threshold = t;
}