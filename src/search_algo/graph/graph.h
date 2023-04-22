#ifndef GRAPH_H
#define GRAPH_H
#include "../node/node.h"
#include "../bpt+/map.h"

using namespace std;
struct SquareGrid {
    typedef vector<node> vectornode;
    static node DIRS[4];

    int width, height;
    Map<node, int> walls;

    SquareGrid(int width_, int height_)
        : width(width_), height(height_) {}

    bool in_bounds(node id) const {
        return 0 <= id.x && id.x < width
            && 0 <= id.y && id.y < height;
    }

    bool passable(node id) const {
        // cout << "called passable\n";
        // cout << walls <<endl;
        return !walls.contains(id);
    }

    vectornode neighbors(node id) const {
        vectornode results;

        for (node dir : DIRS) {
            node next{id.x + dir.x, id.y + dir.y};
            if (in_bounds(next) && passable(next)) {
                results.push_back(next);
            }
        }

        // if ((id.x + id.y) % 2 == 0) {
        // // see "Ugly paths" section for an explanation:
        // std::reverse(results.begin(), results.end());
        // }

    return results;
  }
};


struct GridWithWeights: SquareGrid 
{  
    Map<node, long> forests;
    
    GridWithWeights(int w, int h): SquareGrid(w, h) {}
    double cost(node from_node, node to_node) const {
        return forests.contains(to_node) ? 5 : 1;
    }
};
struct GridWithAStar: GridWithWeights
{
    GridWithAStar(int w, int h): GridWithWeights(w, h) {}
    double heuristic(node a, node b){
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
};

#endif