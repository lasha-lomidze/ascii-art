#include "image_utils.h"
#include "ascii_modes.h"
#include "globals.h"
#include <opencv2/opencv.hpp>
#include <iostream>

// Define globals here
int DEFAULT;
std::unordered_map<std::string, int> size_pixels = {
    {"molecule", 100},
    {"atomic", 150},
    {"terminal-extra-small", 200},
    {"terminal-small", 250},
    {"terminal-medium", 300},
    {"terminal-large", 350},
    {"tiny", 500},
    {"extra-small", 650},
    {"very-small", 750},
    {"small", 900},
    {"normal", DEFAULT}};

int main()
{
    cv::Mat img = create_grayscale_image("examples/puppy.jpg");
    if (img.empty())
    {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    DEFAULT = img.cols;

    img = resized(img, 150);
    draw_in_new_file(img);
    draw_in_terminal(img);

    return 0;
}
