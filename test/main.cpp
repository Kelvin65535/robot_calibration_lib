//
// Created by Kelvin on 2019/11/24.
//

#include "cmake-config.h"
#include "calibration/general_header.h"
#include "calibration/calibration_fileio.h"
#include "calibration/chessboard_calibration.h"

#include "gtest/gtest.h"

#include <experimental/filesystem>
//#include "boost/filesystem/path.hpp"

namespace fs=std::experimental::filesystem;
//namespace fs=boost::filesystem;

auto current_path = fs::path(TEST_PATH);
auto test_image_path = current_path / "test_image";
auto test_yaml_path = current_path / "test_yaml";

using namespace std;

/**
 * Simple image file read test
 */
TEST (OpenCVBasic, ImageRead) {
    std::string image_path = test_image_path / "aruco.jpg";
    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
    ASSERT_FALSE(image.empty());
}

/**
 * basic yaml read test
 */
TEST (YamlBasic, YamlReadTest) {
    // read yaml file
    std::string yamlfile_path = test_yaml_path / "camera_matrix.yaml";
    YAML::Node node = YAML::LoadFile(yamlfile_path);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_FALSE(node.IsNull());
}

/**
 * load camera matrix from yaml file
 */
TEST (CalibrationFileIO, ReadCamMtxFile) {
    // read matrix file
    std::string yamlfile_path = test_yaml_path / "camera_matrix.yaml";
    cv::Mat cam_K_mtx = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    cv::Mat expected_cam_K_mtx = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat expected_distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    ASSERT_TRUE(calibration::read_calibration_param(cam_K_mtx, distCoeffs, yamlfile_path));

    // compare
    cv::Mat diff;
    cv::compare(cam_K_mtx, expected_cam_K_mtx, diff, cv::CMP_NE);
    ASSERT_EQ(cv::countNonZero(diff), 0);

    cv::compare(distCoeffs, expected_distCoeffs, diff, cv::CMP_NE);
    ASSERT_EQ(cv::countNonZero(diff), 0);
}

/**
 * save camera matrix to yaml file
 */
TEST (CalibrationFileIO, SaveCamMtxFile) {
    cv::Mat cam_K_mtx = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    std::string yamlfile_path = test_yaml_path / "camera_matrix.yaml";
    ASSERT_TRUE(calibration::save_calibration_param(cam_K_mtx, distCoeffs, yamlfile_path));
}

/**
 * chessboard calibration
 */
TEST (Calibration, ChessboardCalibration) {
    // read image
    auto chessboard_img_path = test_image_path / "chessboard";
    std::vector<cv::Mat> chessboard_img_arr;
    for (auto img_p : fs::directory_iterator(chessboard_img_path)) {
        cv::Mat image = cv::imread(static_cast<string>(img_p.path()));
        ASSERT_FALSE(image.empty());
        chessboard_img_arr.push_back(image);
    }
    // start calibration
    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    float grid_size = 25; // millimeter
    cv::Size cornerSize(9, 6);
    ASSERT_TRUE(
            calibration::chessboard_calibration(chessboard_img_arr, cameraMatrix, distCoeffs, grid_size, cornerSize));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}