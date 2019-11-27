//
// Created by Kelvin on 2019/11/24.
//

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

int main() {

    std::string image_path = "../aruco.jpg";
    std::cout << image_path << std::endl;

    cv::Mat image;
    image = cv::imread(image_path, cv::IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image);
    cv::waitKey(1);

    return 0;
}