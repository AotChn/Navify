#ifndef SEARCH_ALGO
#define SEARCH_ALGO
#include <utility>
#include <queue>
#include <vector>
#include <iostream>


#include "bpt+/map.h"

using namespace std;

/*From redblobgames "Introuction to A* algorithm && Implement A*" */


template<typename Location, typename Graph>
void a_star_search
  (Graph graph,
   Location start,
   Location goal,
   Map<Location, Location>& came_from,
   Map<Location, double>& cost_so_far)
{
typedef pair<double, Location> pqelement ;
   priority_queue<pqelement, vector<pqelement>, greater<pqelement>> frontier;
   frontier.emplace(pqelement(0, start));
   Location DIR[] = {
    //N                    NE                E              ES
    Location{ 0 ,-1}, Location{ 1 ,-1}, Location{ 1, 0}, Location{ 1 ,1},
    Location{ 0 , 1}, Location{-1 , 1}, Location{-1, 0}, Location{-1 ,-1}
    //S                    SW                W               WN
   };

   came_from[start] = start;
   cost_so_far[start] = 0;
  
   while (!frontier.empty()) {
      Location current = frontier.top().second;
      frontier.pop();

      if (current == goal) {
         break;
      }

      for (Location next : DIR) {
         next += current;

         if(!graph.is_valid(next)) {
            continue;
         }
         double new_cost = cost_so_far[current] + graph.cost(current, next);
         if (cost_so_far.find(next) == cost_so_far.end()
            || new_cost < cost_so_far[next]) {
            cost_so_far[next] = new_cost;
            double priority = new_cost + graph.heuristic(next, goal);
            frontier.emplace(pqelement(priority, next));
            came_from[next] = current;
         }

      }
   }
}


#endif