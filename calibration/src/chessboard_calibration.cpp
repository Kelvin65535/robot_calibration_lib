//
// Created by Kelvin on 2019/11/24.
//

#include "calibration/chessboard_calibration.h"

bool calibration::chessboard_calibration(std::vector<cv::Mat> &images, cv::Mat &cameraMatrix, cv::Mat &distCoeffs,
                                         float gridSize, cv::Size cornerSize) {

    // 2d & 3d point array
    std::vector<std::vector<cv::Point2f> > corners;
    std::vector<std::vector<cv::Point3f> > objectPoints;

    //external param
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;

    // read image
    int skip_img_count = 0;
    for (const auto &img : images) {
        // corner 2d point
        std::vector<cv::Point2f> corner;

        // corner 3d point
        // calculate object 3d point
        std::vector<cv::Point3f> objectPoint;
        for (int i = 0; i < cornerSize.height; ++i)
            for (int j = 0; j < cornerSize.width; ++j)
                objectPoint.push_back(cv::Point3f(j * gridSize, i * gridSize, 0));
        objectPoints.push_back(objectPoint);

        // find pattern
        bool foundCorners;
        foundCorners = cv::findChessboardCorners(img, cornerSize, corner,
                                                 cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);
        if (foundCorners) {
            cv::Mat imgGray;
            cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
            // find subpixel
            cv::cornerSubPix(imgGray, corner, cv::Size(11, 11), cv::Size(-1, -1),
                             cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            // add to corners
            corners.push_back(corner);
        } else {
            // skip this image
            skip_img_count += 1;
        }
    }

    if (skip_img_count >= images.size()) {
        // no usable image
        std::cout << "cannot find any corner in all image, recheck image and calibrate again." << std::endl;
        return false;
    }

    // calibration
    double rms; // return the overall RMS re-projection error.
    rms = cv::calibrateCamera(objectPoints, corners, cornerSize, cameraMatrix, distCoeffs, rvecs, tvecs, 0);
    std::cout << "re-projection error: " << rms << std::endl;

    return true;
}
