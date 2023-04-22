#ifndef IMPORT_IMAGE_H
#define IMPORT_IMAGE_H

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

typedef unsigned char uchar;

uchar** read_from(string file_name, int& row, int& cols) {
    // Load the grayscale image using OpenCV
    cv::Mat img = cv::imread(file_name, cv::IMREAD_GRAYSCALE);

    // Check if the image was loaded successfully
    if (img.empty()) {
        std::cerr << "Error: Could not read image file" << std::endl;
        return nullptr;
    }

    //if (img.empty()) {
		//cout << "Image DNE\n";
	//}else imshow("diedie", img);

    waitKey(0);



    // Convert the image to a 2D array of doubles
    int rows = img.rows;
    int cols = img.cols;



    uchar** imageData = new uchar* [rows];
    for (int i = 0; i < rows; ++i) {
        imageData[i] = new uchar[cols];
        for (int j = 0; j < cols; ++j) {
            imageData[i][j] = (img.at<uchar>(i, j));
        }
    }

    return imageData;
}


#endif