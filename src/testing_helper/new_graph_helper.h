#ifndef NEW_GRAPH_HELPER
#define NEW_GRAPH_HELPER

#include "..\search_algo\new_graph\graph.h"
#include "..\search_algo\node\node.h"
#include "..\search_algo\pixel\pixel.h"
using namespace std;

void add_shade(pixel** arr, int x1, int x2, int y1, int y2){
    for(int y = y1; y <=y2; ++y)
        for(int x = x1; x <= x2; ++x){
            arr[y][x].color = 0;
        }
}
Graph<pixel, node> make_newGraph(){
    pixel** arr;
    int row = 30;
    int col = 30;

    arr = new pixel*[row];
    for(int i = 0; i < row; ++i)
        arr[i] = new pixel[col];

    add_shade(arr, 2,3, 1, 3);
    add_shade(arr, 6,7, 5,9);
    add_shade(arr, 11,11, 0,5);
    add_shade(arr, 12,13, 0,1);
    add_shade(arr, 12,13, 4,5);

    return Graph<pixel, node>(arr, col, row);
}

#endif