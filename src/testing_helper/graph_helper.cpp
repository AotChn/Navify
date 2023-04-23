#include "graph_helper.h"

Map<node, node> get_path(Map<node,node>& parent, node& start, node& goal){
    Map<node,node> p;

    if(!parent.contains(goal)) return p;


    node next = goal, current;
    current = parent[next];
    p.insert(current, next);

    while (!(current == start))
    {
        next = current;
        current = parent[next];
        p.insert(current, next);
        
    }
    
    return p;
}

//Pre: x and y are valid location
//marking node as wall from x1 to x2 (inclusive)
//                      also y1 to y2
void insert_wall(Map<node,int>& wall, int x1, int x2, int y1, int y2){
    for(int x = x1; x <= x2; ++x){
        for(int y = y1; y <=y2; ++y){
            wall.insert(node{x,y}, 1);
        }
    }
    // cout << wall <<endl;
    // cout << "leave insert wall\n";
}

//Pre: x and y are valid location
//marking node as wall from x1 to x2 (inclusive)
//                      also y1 to y2
void insert_forest(Map<node, long>& forest, int x1, int x2, int y1, int y2){
    for(int x = x1; x <= x2; ++x){
        for(int y = y1; y <=y2; ++y){
            forest.insert(node{x,y}, 1);
        }
    }
}

//return a initialized SquareGrid object for testing
//It is a 20 X 10 (w x h), with 3 walls
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

//return a initialized GridWithWeights object for testing
//It have all the feature in diargram1 && also have extra forest area
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

//draw the grid ( . ) = passable tile
//              ( x ) = walls
void draw_grid(SquareGrid& plane){

    for(int y = 0; y < plane.height; ++y){
        for(int x = 0; x < plane.width; ++x){
            if(plane.passable({x,y})) cout << " . ";
            else cout << " x ";
        }
        cout << endl;   
    }
}

//draw the grid ( . ) = passable tile   (Note: if start/goal is not passable or invalid, it won't print corresponding char)
//              ( x ) = walls
//         Arrows (<-, ->, /|, \|) repsenting "WHERE" is ITS parent
//              ( A ) = start
//              ( O ) = goal     
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

//Same with draw_grid(SquareGrid& , Map<node,node>& , node& , node& )
//Extra:       ( F ) = forest : if the tile of(F) have a parent, it would print the arrow instead.
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

//Print travsed node's cost
void draw_grid(SquareGrid& plane, Map<node, double>& cost, node& start, node& goal){
    for(int y = 0; y < plane.height; ++y){
        for(int x = 0; x < plane.width; ++x){
            if(plane.passable({x,y})) {
                if(node{x,y} == start)
                    cout << "   A";
                else if(node{x,y} == goal)
                    cout << "   O";
                else if(cost.contains(node{x,y}))
                    cout << setw(4) << cost[node{x,y}];
                else cout << "   .";
            }
            else cout << "   X";
        }
        cout << endl ;   
    }
}

void draw_path(GridWithWeights& plane, Map<node, node>& parent, node& start, node& goal){
    auto path = get_path(parent, start, goal);
    for(int y = 0; y < plane.height; ++y){
        for(int x = 0; x < plane.width; ++x){
            if(plane.passable({x,y})) {
                if(node{x,y} == goal)
                    cout << "  O  "; 
                else if(node{x,y} == start)
                    cout << "  A  ";
                else if(path.contains({x,y}))
                    cout << "  @  ";
                else if(plane.forests.contains(node{x,y}))
                    cout << "  F  ";
                else
                    cout << "  .  ";
            }
            else cout << "  x  ";
        }
        cout << endl ;   
    }
}

