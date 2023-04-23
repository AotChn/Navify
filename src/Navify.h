#ifndef NAVIFY_H
#define NAVIFY_H

// #include "open_cv/import_image.h"
#include "search_algo/Algo.hpp"
#include <tuple>
#include "testing_helper/graph_helper.h"
// #include <opencv2/opencv.hpp>
using namespace std;

class Navify{
public:
    bool import_image(string image_name);
    bool run();
    void display();

    void set_start(node src){start = src;}
    void set_goal(node dest){goal = dest;}
// private:
    typedef Graph<pixel, node> graph;
    graph _Grayed_graph;
    std::tuple<pair<node, node>, Map<node,node>, string> path;
    node start, goal;
    string _image_name;
};
#endif