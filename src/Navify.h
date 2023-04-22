#ifndef NAVIFY_H
#define NAVIFY_H

// #include "open_cv/import_image.h"
#include "search_algo/Algo.hpp"

class Navify{
public:
    bool import_image(string image_name);
    bool run();
    void display();
// private:
    Graph<pixel, node> _graph;

};
#endif