#ifndef GRAPH_HELPER
#define GRAPH_HELPER

#include <iostream>
#include "../search_algo/graph/graph.h"

using namespace std;
void insert_wall(Map<node,int>& wall, int x1, int x2, int y1, int y2){
    for(int x = x1; x <= x2; ++x){
        for(int y = y1; y <=y2; ++y){
            wall.insert(node{x,y}, 1);
        }
    }
    // cout << wall <<endl;
    // cout << "leave insert wall\n";
}
void insert_forest(Map<node, long>& forest, int x1, int x2, int y1, int y2){
    for(int x = x1; x <= x2; ++x){
        for(int y = y1; y <=y2; ++y){
            forest.insert(node{x,y}, 1);
        }
    }
}
SquareGrid make_diagram1(){
    SquareGrid plane(20, 10);



    plane.walls.insert(node{2,1}, 1);
    plane.walls.insert(node{2,2}, 1);
    plane.walls.insert(node{2,3}, 1);
    
    plane.walls.insert(node{3,1}, 1);
    plane.walls.insert(node{3,2}, 1);
    plane.walls.insert(node{3,3}, 1);

    insert_wall(plane.walls, 6,7, 5,9);
    insert_wall(plane.walls, 11,11, 0,5);
    insert_wall(plane.walls, 12,13, 0,1);
    insert_wall(plane.walls, 12,13, 4,5);
    return plane;
}

GridWithWeights make_diagram2(){
    GridWithWeights plane(20,10);
    plane.walls.insert(node{2,1}, 1);
    plane.walls.insert(node{2,2}, 1);
    plane.walls.insert(node{2,3}, 1);
    
    plane.walls.insert(node{3,1}, 1);
    plane.walls.insert(node{3,2}, 1);
    plane.walls.insert(node{3,3}, 1);

    insert_wall(plane.walls, 6,7, 5,9);
    insert_wall(plane.walls, 11,11, 0,5);
    insert_wall(plane.walls, 12,13, 0,1);
    insert_wall(plane.walls, 12,13, 4,5);

    insert_forest(plane.forests, 4,7,0,3);
    plane.forests.insert(node{3,0}, 1);
    
    return plane;
}

void draw_grid(SquareGrid& plane){

    for(int y = 0; y < plane.height; ++y){
        for(int x = 0; x < plane.width; ++x){
            if(plane.passable({x,y})) cout << " . ";
            else cout << " x ";
        }
        cout << endl;   
    }
}

void draw_grid(SquareGrid& plane, Map<node,node>& parent, node& start, node& goal){
    for(int y = 0; y < plane.height; ++y){
        for(int x = 0; x < plane.width; ++x){
            if(plane.passable({x,y})) {
                if(parent.contains({x,y})){
                    if(node{x,y} == goal) cout << "  O  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[0])cout << " /|  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[1])cout << " ->  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[2]) cout << " \\|  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[3]) cout << " <-  ";
                    else if(parent[{x,y}] == start){
                        cout << "  A  ";
                    }
                }
                else cout << "  .  ";
            }
            else cout << "  x  ";
        }
        cout << endl ;   
    }
}

void draw_grid(GridWithWeights& plane, Map<node,node>& parent, node& start, node& goal){
    for(int y = 0; y < plane.height; ++y){
        for(int x = 0; x < plane.width; ++x){
            if(plane.passable({x,y})) {
                if(parent.contains({x,y})){
                    if(node{x,y} == goal) cout << "  O  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[0])cout << " /|  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[1])cout << " ->  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[2]) cout << " \\|  ";
                    else if(parent[{x,y}] - node{x,y} == SquareGrid::DIRS[3]) cout << " <-  ";
                    else if(parent[{x,y}] == start){
                        cout << "  A  ";
                    }
                }
                else if(plane.forests.contains({x,y})) cout << "  F  ";
                else cout << "  .  ";
            }
            else cout << "  x  ";
        }
        cout << endl ;   
    }

}

#endif