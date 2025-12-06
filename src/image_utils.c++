#include "image_utils.h"
#include "globals.h"
#include <opencv2/opencv.hpp>

int get_pixels_size(const std::string &size_name)
{
    if (size_pixels.count(size_name))
        return size_pixels[size_name];
    return size_pixels["normal"];
}

cv::Mat create_image(const std::string &image_path)
{
    return cv::imread(image_path);
}

cv::Mat create_grayscale_image(const std::string &image_path)
{
    return cv::imread(image_path, cv::IMREAD_GRAYSCALE);
}

cv::Mat resized(const cv::Mat &img, int width)
{
    cv::Mat resized_img;
    int height = width * img.rows / img.cols;
    cv::resize(img, resized_img, cv::Size(width, height));
    return resized_img;
}

cv::Mat resized(const cv::Mat &img, const std::string &size_name)
{
    int width = get_pixels_size(size_name);
    return resized(img, width);
}

// & Modes to add:
// * Grayscale ASCII (already have) 
// Color ASCII (truecolor / 256-color terminal)
// * Block-characters mode (▀ ▄ █ ▌▐ etc → looks much sharper)
// Edge-detection mode (ASCII outlines via Sobel filter)
// open in termina/txt-file/browser/window/image/window_terminal
// & Add (other):
// “fast mode” (nearest neighbor)
// “HQ mode” (bilinear / bicubic resize)
// performance benchmark printed at the end
// CLI
// non disorted ( resize the image )