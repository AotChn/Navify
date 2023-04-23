#ifndef BREADTH_H
#define BREADTH_H
#include <queue>
#include "../graph/graph.h"
#include "../bpt+/map.h"

using namespace std;
Map<node, node> breadth_first_search(SquareGrid graph, node start, node goal = {-1,-1}){
/*

  std::queue<Location> frontier;
  frontier.push(start);

  std::unordered_map<Location, Location> came_from;
  came_from[start] = start;

  while (!frontier.empty()) {
    Location current = frontier.front();
    frontier.pop();

    for (Location next : graph.neighbors(current)) {
      if (came_from.find(next) == came_from.end()) {
        frontier.push(next);
        came_from[next] = current;
      }
    }
  }
  return came_from;
}
*/
    queue<node> frontier;
    frontier.push(start);
    Map<node,node> came_from;
    came_from[start] = start;

    while (!frontier.empty())
    { 
      node current = frontier.front();
      frontier.pop();
    
      if(current == goal) break;
      
      for(node next: graph.neighbors(current)){
          if(!came_from.contains(next))
          {
              frontier.push(next);
              came_from[next] = current;
          }
      }
    }
    
    return came_from;
}
#endif