#ifndef GRAPH_HELPER
#define GRAPH_HELPER

#include <iostream>
#include "../search_algo/graph/graph.h"

using namespace std;



Map<node, node> get_path(Map<node,node>& parent, node& start, node& goal);
//Pre: x and y are valid location
//marking node as wall from x1 to x2 (inclusive)
//                      also y1 to y2
void insert_wall(Map<node,int>& wall, int x1, int x2, int y1, int y2);

//Pre: x and y are valid location
//marking node as wall from x1 to x2 (inclusive)
//                      also y1 to y2
void insert_forest(Map<node, long>& forest, int x1, int x2, int y1, int y2);

//return a initialized SquareGrid object for testing
//It is a 20 X 10 (w x h), with 3 walls
SquareGrid make_diagram1();
//return a initialized GridWithWeights object for testing
//It have all the feature in diargram1 && also have extra forest area
GridWithWeights make_diagram2();
//draw the grid ( . ) = passable tile
//              ( x ) = walls
void draw_grid(SquareGrid& plane);

//draw the grid ( . ) = passable tile   (Note: if start/goal is not passable or invalid, it won't print corresponding char)
//              ( x ) = walls
//         Arrows (<-, ->, /|, \|) repsenting "WHERE" is ITS parent
//              ( A ) = start
//              ( O ) = goal     
void draw_grid(SquareGrid& plane, Map<node,node>& parent, node& start, node& goal);
//Same with draw_grid(SquareGrid& , Map<node,node>& , node& , node& )
//Extra:       ( F ) = forest : if the tile of(F) have a parent, it would print the arrow instead.
void draw_grid(GridWithWeights& plane, Map<node,node>& parent, node& start, node& goal);
//Print travsed node's cost
void draw_grid(SquareGrid& plane, Map<node, double>& cost, node& start, node& goal);

void draw_path(GridWithWeights& plane, Map<node, node>& parent, node& start, node& goal);


#endif