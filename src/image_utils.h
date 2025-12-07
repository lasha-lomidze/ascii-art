#pragma once
#include <opencv2/opencv.hpp>
#include <string>

cv::Mat create_image(const std::string &image_path);
cv::Mat create_grayscale_image(const std::string &image_path);
cv::Mat resized(const cv::Mat &img, int width);
cv::Mat resized(const cv::Mat &img, const std::string &size_name);
int get_pixels_size(const std::string &size_name);
