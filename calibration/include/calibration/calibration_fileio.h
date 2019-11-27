//
// Created by Kelvin on 2019/11/25.
//

#ifndef ROBOT_CALIBRATION_LIB_CALIBRATION_FILEIO_H
#define ROBOT_CALIBRATION_LIB_CALIBRATION_FILEIO_H

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "general_header.h"

namespace calibration {
    bool read_calibration_param(cv::Mat &cameraMatrix, cv::Mat &distCoeffs, const std::string &yaml_path);

    bool save_calibration_param(const cv::Mat &camera_matrix, const cv::Mat &dist_coeffs, const std::string &yaml_path);
}

#endif //ROBOT_CALIBRATION_LIB_CALIBRATION_FILEIO_H
