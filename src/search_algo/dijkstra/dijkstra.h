#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <queue>
#include "../graph/graph.h"
#include "../bpt+/map.h"

using namespace std;


Map<node,node> dijkstra_search(GridWithWeights& graph, node start, node goal){
    typedef pair<double,node> pqelement;
    priority_queue<pqelement, std::vector<pqelement>, greater<pqelement>> frontier;
    frontier.emplace(pqelement{0,start});
    Map<node,node> came_from;

    Map<node, double> cost_so_far;
    
    
    came_from[start] = start;
    cost_so_far[start] = 0;


    while (!frontier.empty())
    {   
        // cout << "current_p : " << frontier.top().first << "from: " << frontier.top().second << endl;

        node current = frontier.top().second;
        frontier.pop();

        if(current == goal) break;

        for(node next : graph.neighbors(current)){
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if(!came_from.contains(next) || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                frontier.emplace(pqelement{new_cost, next});
                came_from[next] = current;
                if(next == goal) break;

            }
        }
    }
    
    return came_from;
}

#endif