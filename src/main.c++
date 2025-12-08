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
    // cv::Mat img = create_grayscale_image("examples/dady.jpg");
    cv::Mat img = create_image("examples/qevxo.png");
    if (img.empty())
    {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    DEFAULT = img.cols;

    img = resized(img, 250);

    // draw_in_new_file(img);
    // draw_in_terminal(img);
    draw_in_terminal_vivid(img);

    return 0;
}

// choose colored,
// choose drawign mode
// choose where to draw
// performance benchmark
// choose edge detection toggle

// ^ warn user about use of ide if he tries to run from it, but give him the chance

// maybe add grayscale_to_ansii so that i can do it in one color

// ! how about transparent images

// & Modes to add:
// * Grayscale ASCII (already have)
// ^ Color ASCII
// ^ Color ASCII bg
// * Block-characters mode (▀ ▄ █ ▌▐ etc → looks much sharper)
// Edge-detection mode (ASCII outlines via Sobel filter)
// open in termina/txt-file/browser/window/image/window_terminal
// & Add (other):
// “fast mode” (nearest neighbor)
// “HQ mode” (bilinear / bicubic resize)
// performance benchmark printed at the end
// CLI
// ^ non disorted ( resize the image )
