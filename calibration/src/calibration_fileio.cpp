//
// Created by Kelvin on 2019/11/25.
//

#include "calibration/calibration_fileio.h"

namespace fs=std::experimental::filesystem;


bool calibration::save_calibration_param(const cv::Mat &camera_matrix, const cv::Mat &dist_coeffs,
                                         const std::string &yaml_path) {

    // compare matrix size
    if (camera_matrix.size() != cv::Size(3, 3)) {
        std::cout << "camera matrix size error" << std::endl;
        return false;
    }

    if (dist_coeffs.size() != cv::Size(1, 5)) {
        std::cout << "dist matrix size error, get size: " << dist_coeffs.size() << std::endl;
        return false;
    }

    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    // camera matrix
    std::vector<double> cam_mtx_vec;
    cam_mtx_vec.assign((double *) camera_matrix.datastart, (double *) camera_matrix.dataend);
    emitter << YAML::Key << "cam_K" << YAML::Value << YAML::Flow << cam_mtx_vec;
    // dist coeffs
    std::vector<double> cam_dist_vec;
    cam_dist_vec.assign((double *) dist_coeffs.datastart, (double *) dist_coeffs.dataend);
    emitter << YAML::Key << "cam_dist" << YAML::Value << YAML::Flow << cam_dist_vec;
    emitter << YAML::EndMap;

    if (!emitter.good()) {
        std::cout << "yaml parse error" << std::endl;
        return false;
    }

    std::ofstream fout(yaml_path);
    if (fout.is_open()) {
        fout << emitter.c_str();
        fout.close();
        return true;
    } else {
        std::cout << "file write error" << std::endl;
        return false;
    }
}

bool calibration::read_calibration_param(cv::Mat &cameraMatrix, cv::Mat &distCoeffs,
                                         const std::string &yaml_path) {
    // read yaml
    YAML::Node chessboard_yaml;
    try {
        chessboard_yaml = YAML::LoadFile(yaml_path);
    } catch (YAML::Exception &exception) {
        std::cout << "YAML file path error" << std::endl;
        return false;
    }

    // camera matrix
    auto cam_K_node = chessboard_yaml["cam_K"];
    auto cam_k_vec = cam_K_node.as<std::vector<double> >();
    cv::Mat t(cam_k_vec, CV_64F);
    cameraMatrix = t.reshape(0, 3).clone();

    // dist coeffs
    auto cam_C_node = chessboard_yaml["cam_dist"];
    auto cam_C_vec = cam_C_node.as<std::vector<double> >();
    distCoeffs = cv::Mat(cam_C_vec, CV_64F).clone();

    return true;
}
