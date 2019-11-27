//
// Created by Kelvin on 2019/11/24.
//

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "opencv2/aruco.hpp"

int main() {

    std::string image_path = "../aruco.jpg";

//    std::cout << image_path << std::endl;

    cv::Mat image;
    image = cv::imread(image_path, cv::IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
//    cv::imshow("Display Image", image);
//    cv::waitKey(1);

    // detection arUco marker
    for (int i = cv::aruco::DICT_4X4_50; i < cv::aruco::DICT_APRILTAG_36h11; ++i) {
//        cv::aruco::PREDEFINED_DICTIONARY_NAME d = static_cast<cv::aruco::PREDEFINED_DICTIONARY_NAME>(i);
        auto d = cv::aruco::DICT_6X6_250;
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(d);
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
        cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
        cv::aruco::detectMarkers(image, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

        if (!markerIds.empty()) {
            std::cout << "Dictionary name is " << d << std::endl;
            cv::aruco::drawDetectedMarkers(image, markerCorners, markerIds);
            cv::imshow("Display Image", image);
            cv::waitKey(0);
            break;
        }
    }


    return 0;
}