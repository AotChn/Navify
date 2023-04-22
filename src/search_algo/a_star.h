#ifndef SEARCH_ALGO
#define SEARCH_ALGO
#include <queue>
#include <utility>
	
#include "constants.h"
#include "a_star_helper.h"

using namespace std;

/*From redblobgames "Introuction to A* algorithm"

frontier = PriorityQueue()
frontier.put(start, 0)
came_from = dict()
cost_so_far = dict()
came_from[start] = None
cost_so_far[start] = 0

while not frontier.empty():
   current = frontier.get()

   if current == goal:
      break
   
   for next in graph.neighbors(current):
      new_cost = cost_so_far[current] + graph.cost(current, next)
      if next not in cost_so_far or new_cost < cost_so_far[next]:
         cost_so_far[next] = new_cost
         priority = new_cost + heuristic(goal, next)
         frontier.put(next, priority)
         came_from[next] = current
*/

// typedef double priority;

// bool operator <(pair<double, node> lhs, pair<double, node> rhs){
//     return lhs.first > rhs.first;
// }

// bool a_star(long graph[][COL], const node& start, const node& goal){
//     priority_queue<pair<double, node>>frontier;
//     Map<node, double> cost_so_far;
//     Map<node, node> came_from;


//     //init
//     frontier.push(pair<double,node>(0, start));
//     node noll;
//     came_from[start] = noll;
//     cost_so_far[start] = 0;



//     if(!is_valid(start) || is_blocked(graph, start)|| !is_valid(goal) || is_blocked(graph, goal)){
//         cout << "start/goal is blocked/not valid\n";
//         return false;       //If goal/start is not a valid node;
//     }
    
//     while (!frontier.empty())
//     {   
//         auto current = frontier.top();
//         frontier.pop();
//         if(current.second == goal) {
//             print_path(came_from, goal);
//             return true;
//         }
//         for(node next : its_neighbor(current.second)){

//             double new_cost = cost_so_far[current.second] + 1;

//             if(is_valid(next) && !is_blocked(graph, next))
//                 if(!cost_so_far.contains(next)|| new_cost < (cost_so_far[next])){
//                     cost_so_far[next] = new_cost;
//                     cout << "next: " << next << " , cost: " << new_cost << ", from: "  << current.second << endl;
//                     double priority = new_cost + hueristic(next, goal);
//                     came_from[next] = current.second;
//                     frontier.emplace(pair<double,node>(priority, next));
//                 }
//         }

//     }

//     cout << "Path Not found!\n";
//     return false;
// }
#endif