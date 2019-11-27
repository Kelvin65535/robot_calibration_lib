//
// Created by Kelvin on 2019/11/24.
//

#ifndef ROBOT_CALIBRATION_LIB_CHESSBOARD_CALIBRATION_H
#define ROBOT_CALIBRATION_LIB_CHESSBOARD_CALIBRATION_H

//#include "opencv2/core/core.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"

#include "general_header.h"

#include <iostream>

namespace calibration {
    /// start chessboard calibration
    /// \param images input image arrays
    /// \param cameraMatrix output camera matrix
    /// \param distCoeffs output dist coeffs
    /// \param gridSize input block grid size in millimeter
    /// \param cornerSize input corner size in cv::Size(width_corner_count, height_corner_count)
    /// \return true: calibration success
    bool chessboard_calibration(std::vector<cv::Mat> &images, cv::Mat &cameraMatrix,
                                cv::Mat &distCoeffs, float gridSize, cv::Size cornerSize);
}

#endif //ROBOT_CALIBRATION_LIB_CHESSBOARD_CALIBRATION_H
