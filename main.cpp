#include "img_proc.h"




int main(){
    open_image("40x40.png");
    Mat img = imread("40x40.png");
    std::cout << std::endl << img << std::endl;
    return 0;
}