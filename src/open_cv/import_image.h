#ifndef IMPORT_IMAGE_H
#define IMPORT_IMAGE_H

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "../search_algo/pixel/pixel.h"


using namespace std;
using namespace cv;

typedef unsigned char uchar;

pixel** read_image(string image_name, int& rows, int& cols) {
    // Load the grayscale image using OpenCV
    cv::Mat img = cv::imread(image_name, cv::IMREAD_GRAYSCALE);

    // Check if the image was loaded successfully
    if (img.empty()) {
        std::cerr << "Error: Could not read image file" << std::endl;
        return nullptr;
    }

    // Convert the image to a 2D array of uchar (like uint but 0 - 255)
    rows = img.rows;
    cols = img.cols;

    pixel** imageData = new pixel* [rows];
    for (int i = 0; i < rows; ++i) {
        imageData[i] = new pixel[cols];
        for (int j = 0; j < cols; ++j) {
            imageData[i][j].color = (img.at<uchar>(i, j));
            imageData[i][j].cost = 1;
        }

    }


    return imageData;
}
#endif