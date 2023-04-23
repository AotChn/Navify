#include "graph.h"


node SquareGrid::DIRS[4] = {
    //N             E
    node{ 0 ,-1}, node{ 1, 0},
    node{ 0 , 1}, node{-1, 0}
    //S             W
};