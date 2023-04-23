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
    Graph(const Graph& other){
        clear();
        width = other.width;
        height = other.height;
        if(other._grid != nullptr){
            _grid = new graph_t[height]
            for(int i = 0; i < height; ++i)
                for(int j = 0; j < width; ++j)
                    _grid[j][i] = other._grid[j][i];
        }
    }
    ~Graph(){clear()}
    
    //Accessor
    bool is_vaild(){return _grid != nullptr && width > 0 && height > 0}
    bool in_bounds(node_t id) const ;   //true if id is inbound;
    bool is_blocked(node_t id) const ;  //true if id is blocked
    bool is_valid(node_t id) const;     //true if id is inbound && !blocked
    double cost(node_t from_node, node_t to_node) const; 
    double heuristic(node_t a, node_t b) const;

    //setter
    void shallow_setter(graph_t** picture, int w, int h){
        _grid = picture;
        width = w;
        height = h;
    }
    static void set_threshold(int t);
private:
    clear(){
        if(_grid == nullptr) return;
        for(int i = 0; i < height; ++i)
            delete [] _grid[i];
        delete [] _grid;
        _grid = nullptr;
    }
        
    int width, height;
    graph_t** _grid;
    static int threshold;
};

#include "graph.cpp"
#endif