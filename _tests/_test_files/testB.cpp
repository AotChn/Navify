#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../src\search_algo\a_star.h"

#include "../../src/testing_helper/graph_helper.h"
#include "../../src\search_algo\breadth\breadth.h"
#include "../../src\search_algo\dijkstra\dijkstra.h"
#include "../../src/pixel_file/pixel_file.h"

//For showing how to use PQueue and std::pair
TEST(STD_PQ, DISABLED_test1){

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

TEST(OTHER, DISABLED_not_weighted){
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

TEST(OTHER, DISABLED_weighted){
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

TEST(ASTAR, DISABLED_test1){
    GridWithAStar graph(20,10);
    auto temp = make_diagram2();

    graph.walls = temp.walls;
    graph.forests = temp.forests;
    
    node start = {0, 0};
    node goal = {10, 2};
    Map<node,node> came_from;
    Map<node,double> cost_so_far;
    
    cout << "A*:\n";
    a_star_search(graph,start,goal, came_from, cost_so_far);

    draw_grid(graph,came_from, start, goal);
    cout << "\n\n";

    cout << "A* _cost:\n";
    draw_grid(graph,cost_so_far, start, goal);
    cout << "\n\n";

    cout << "A* _path:\n";
    draw_path(graph, came_from, start, goal);
    cout << "\n\n";
}

TEST(ASTAR, new_graph){
    

}
TEST(PIXEL, readRows){
    string file_name = "C:\\Users\\001\\source\\repos\\OpenCV_test\\x64\\pixel.bin";
    // "pixel.bin";
    
    // uchar arr[5] = {10, 55, 60, 200, 255};
    // write_to(file_name, arr, 5);
    // read_from(file_name, 5);
    read_from(file_name);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

/*

----------running testB.cpp---------


[==========] Running 3 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from STD_PQ
[ RUN      ] STD_PQ.test1
0
1
2
3
4




1
[       OK ] STD_PQ.test1 (1 ms)
[----------] 1 test from STD_PQ (2 ms total)

[----------] 2 tests from ASTAR
[ RUN      ] ASTAR.test1
A*:
  A   <-   <-   <-   <-    F    F    F    .    .    .    x    x    x    .    .    .    .    .    .  
 /|   <-    x    x    F    F    F    F   \|   \|    .    x    x    x    .    .    .    .    .    .  
 /|   <-    x    x    F    F    F   ->   \|   <-    O    x    .    .    .    .    .    .    .    .  
 /|   /|    x    x   \|   \|   \|   \|   \|   <-   <-    x    .    .    .    .    .    .    .    .  
 /|   /|   <-   <-   <-   <-   <-   <-   <-   <-   <-    x    x    x    .    .    .    .    .    .  
 /|   /|   /|   /|   /|   /|    x    x   /|   /|    .    x    x    x    .    .    .    .    .    .  
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .  
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .  
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .  
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .  


A* _cost:
   A   1   2   7  12   .   .   .   .   .   .   X   X   X   .   .   .   .   .   .
   1   2   X   X   .   .   .   .  15  16   .   X   X   X   .   .   .   .   .   .
   2   3   X   X   .   .   .  19  14  15   O   X   .   .   .   .   .   .   .   .
   3   4   X   X  13  14  15  16  13  14  15   X   .   .   .   .   .   .   .   .
   4   5   6   7   8   9  10  11  12  13  14   X   X   X   .   .   .   .   .   .
   5   6   7   8   9  10   X   X  13  14   .   X   X   X   .   .   .   .   .   .
   .   .   .   .   .   .   X   X   .   .   .   .   .   .   .   .   .   .   .   .
   .   .   .   .   .   .   X   X   .   .   .   .   .   .   .   .   .   .   .   .
   .   .   .   .   .   .   X   X   .   .   .   .   .   .   .   .   .   .   .   .
   .   .   .   .   .   .   X   X   .   .   .   .   .   .   .   .   .   .   .   .


A* _path:
  A    .    .    F    F    F    F    F    .    .    .    x    x    x    .    .    .    .    .    .
  @    .    x    x    F    F    F    F    .    .    .    x    x    x    .    .    .    .    .    .
  @    @    x    x    F    F    F    F    @    @    O    x    .    .    .    .    .    .    .    .
  .    @    x    x    F    F    F    F    @    .    .    x    .    .    .    .    .    .    .    .  
  .    @    @    @    @    @    @    @    @    .    .    x    x    x    .    .    .    .    .    .
  .    .    .    .    .    .    x    x    .    .    .    x    x    x    .    .    .    .    .    .
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .  
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .
  .    .    .    .    .    .    x    x    .    .    .    .    .    .    .    .    .    .    .    .


[       OK ] ASTAR.test1 (122 ms)
[ RUN      ] ASTAR.new_graph
[       OK ] ASTAR.new_graph (0 ms)
[----------] 2 tests from ASTAR (124 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test suites ran. (128 ms total)
[  PASSED  ] 3 tests.

  YOU HAVE 2 DISABLED TESTS

*/