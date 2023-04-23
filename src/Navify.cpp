#include "Navify.h"
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
    get<2>(path) = image_name;
    return true;
}
bool Navify::run(){
    if(!_Grayed_graph.is_vaild()){
        cout << "Image is not set up properly\n";
        return false;
    } 
    Map<node, node> parent;
    Map<node, double> cost_so_far;

    a_star_search<node, graph>(_Grayed_graph, start,goal, parent,cost_so_far);
    get<1>(path) = get_path(parent, start, goal);
    get<0>(path) = {start, goal};
    return true;
}
void Navify::display(){
    if(_image_name != get<2>(path)){
        cout << "Last import fail, so following image is from: " << get<2>(path) <<endl;
    }

     cv::Mat img = cv::imread(get<2>(path));
     if (img.empty()) {
         std::cerr << "Error: Could not read image file" << std::endl;
         return;
     }

    node DIR[] = {
    //N                    NE                E              ES
    node{ 0 ,-1}, node{ 1 ,-1}, node{ 1, 0}, node{ 1 ,1},
    node{ 0 , 1}, node{-1 , 1}, node{-1, 0}, node{-1 ,-1}
    //S                    SW                W               WN
   };

    node current = get<0>(path).first;
    while (!(current == get<0>(path).second)) {
            img.at<Vec3b>(current.y, current.x) = { 255,0,0 };

 /*        for (auto x : DIR) {
             if (!_Grayed_graph.in_bounds(current + x))
                 continue;
             auto t = current + x;
             img.at<Vec3b>(t.y, t.x) = { 255,0,0 };


          }*/
             current = get<1>(path)[current];
    }

    imshow("diedie", img);
    waitKey(0);

}