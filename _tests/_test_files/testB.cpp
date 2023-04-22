#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../src\search_algo\a_star.h"

#include "../../src/testing_helper/graph_helper.h"
#include "../../src\search_algo\breadth\breadth.h"
#include "../../src\search_algo\dijkstra\dijkstra.h"

TEST(STD_PQ, test1){

	// comparator: greater -> the smaller of the value is
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 0; i < 5; ++i){
		pq.emplace(i);
	}

	while (!pq.empty())
	{
		cout << pq.top() << endl;

		pq.pop();
	}
	cout << "\n\n\n";

	cout << (pair<int,int>(1,123123) < pair<int,int>(2,0)) << endl; //shows when comparing std::pair, it is return p1.first < p2.first
	
}

TEST(OTHER, not_weighted){
	SquareGrid plane = make_diagram1();
    node start = {0, 0};
    node goal = {10, 2};
    Map<node,node> parent;


	cout << "\n\n\t====case 1====\n\n";
    parent = breadth_first_search(plane, start, goal);
    cout << "BD:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";
    
    GridWithWeights plane_weighted(plane.width, plane.height);
    plane_weighted.walls = plane.walls;

    parent = dijkstra_search(plane_weighted, start, goal);
    cout << "Dijkstra:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";

    //=======
    goal = {15, 3};

	cout << "\n\n\t====case 2====\n\n";

    parent = breadth_first_search(plane, start, goal);
    cout << "BD:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";


    parent = dijkstra_search(plane_weighted, start, goal);
    cout << "Dijkstra:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";

    cout << "\n\n\n";
}

TEST(OTHER, weighted){
	auto plane = make_diagram2();
    node start = {0, 0};
    node goal = {10, 2};
    Map<node,node> parent;


	cout << "\n\n\t====case 1====\n\n";
    parent = breadth_first_search(plane, start, goal);
    cout << "BD:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";
    


    parent = dijkstra_search(plane, start, goal);
    cout << "Dijkstra:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";

    //=======
    goal = {15, 3};

	cout << "\n\n\t====case 2====\n\n";

    parent = breadth_first_search(plane, start, goal);
    cout << "BD:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";


    parent = dijkstra_search(plane, start, goal);
    cout << "Dijkstra:\n";
    draw_grid(plane, parent, start, goal);
    cout << "\n\n";

    cout << "\n\n\n";

}

TEST(ASTAR, test1){
    GridWithAStar graph(20,10);
    auto temp = make_diagram2();

    graph.walls = temp.walls;
    graph.forests = temp.forests;
    
    node start = {0, 0};
    node goal = {10, 2};
    Map<node,node> came_from;
    Map<node,double> cost_so_far;
    a_star_search(graph,start,goal, came_from, cost_so_far);

    draw_grid(graph,came_from, start, goal);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

