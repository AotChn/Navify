#include "Navify.h"
#include "testing_helper/graph_helper.h"
bool Navify::import_image(string image_name){
    _image_name = image_name;
    int c, r;
    pixel** arr = read_image(image_name,r,c);
    if(arr == nullptr){
        return false;
    }

    _Grayed_graph.clear();
    _Grayed_graph.shallow_setter(arr, c, r);

    if(!_Grayed_graph.is_vaild()){
        cout << "[Debug] : [Navify::import_image] : graph is invalid evethoug image is read\n";
        return false;
    }
    get<0>(path)= image_name;
    return true;
}
bool Navify::run(node start_, node goal_){
    if(!_Grayed_graph.is_vaild()){
        cout << "Image is not set up properly\n";
        return false;
    } 
    Map<node, node> parent;
    Map<node, double> cost_so_far;

    start = start_;
    goal = goal_;

    a_star_search<node, graph>(_Grayed_graph, start,goal, parent,cost_so_far);
    get<1>(path) = get_path(parent, start, goal);
    get<2>(path) = {start, goal};
    return true;
}
void Navify::display(){
    if(_image_name != get<0>(path)){
        cout << "Last import fail, so following image is from: " << get<0>(path)<<endl;
    }

    cv::Mat img = cv::imread(get<0>(path));
    if (img.empty()) {
        std::cerr << "Error: Could not read image file" << std::endl;
        return nullptr;
    }
    

    auto DIR[] = {
    //N                    NE                E              ES
    node{ 0 ,-1}, node{ 1 ,-1}, node{ 1, 0}, node{ 1 ,1},
    node{ 0 , 1}, node{-1 , 1}, node{-1, 0}, node{-1 ,-1}
    //S                    SW                W               WN
   };

    for(auto it = get<1>(path).begin(); it != get<1>(path).end(); ++it){
        img.at((*it).key.x, (*it).key.y) = 255;
    }

    imshow("diedie", img);
}