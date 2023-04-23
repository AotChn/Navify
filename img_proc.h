#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H


#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;
  
int open_image(std::string img_name){
    Mat image = imread(img_name);
    if (image.empty()) {
        cout << "Image File " << "Not Found" << endl;
        cin.get();
        return -1;
    }
    imshow(img_name, image);
    // Wait for any keystroke
    waitKey(0);
    return 0;
}

void to_array(Mat img, double * ptrDst[img.rows]){
cv::Mat dst;
// Convert to double (much faster than a simple for loop)
img.convertTo(dst, CV_64F, 1, 0);
    for(int i = 0; i < dst.rows; ++i) {
        ptrDst[i] = dst.ptr<double>(i);

        for(int j = 0; j < dst.cols; ++j) {
            double value = ptrDst[i][j];
        }
    }
} 

void print_arr(double * arr[40]){
    for(int i=0; i<40; i++){
        for(int j=0; j<40; j++){
            std::cout<<arr[i][j];
        }
    }
}

Mat grey_scale(Mat img){
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    return img_gray;
}

Mat blur(Mat img){
    Mat img_blur;
    GaussianBlur(img, img_blur, Size(11,11), 0);
    return img_blur;
}

Mat sobelx(Mat img){
    Mat img_x;
    Sobel(img, img_x, CV_64F, 1, 0, 5);
    return img_x;
}
Mat sobely(Mat img){
    Mat img_y;
    Sobel(img, img_y, CV_64F, 0, 1, 5);
    return img_y;
}
Mat sobelxy(Mat img){
    Mat img_xy;
    Sobel(img, img_xy, CV_64F, 1, 1, 5);
    return img_xy;
}

Mat canny(Mat img){
    Mat canny;
    Canny(img, canny, 70, 170, 5, false);
    return canny;
}

int edge_detect(std::string img_name){
    Mat img = imread(img_name);
    if (img.empty()) {
        cout << "Image File " << "Not Found" << endl;
        cin.get();
        return -1;
    }
    Mat grey = grey_scale(img);
    Mat blr = blur(grey);
    Mat s_x = sobelx(blr);
    Mat s_y = sobely(blr);
    Mat s_xy = sobelxy(blr);
    Mat c = canny(blr);

    imshow(img_name, img);
    imshow("grey", grey);
    imshow("blur", blr);
    imshow("sobel x", s_x);
    imshow("sobel y", s_y);
    imshow("sobel xy", s_xy);
    imshow("canny", c);
    waitKey(0);

    return 0;
}


#endif