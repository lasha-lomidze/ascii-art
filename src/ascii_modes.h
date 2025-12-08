#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "globals.h"

// reset ANSI escape
extern const std::string ANSI_RESET;

// ASCII conversions
char grayscale_to_ascii(unsigned char pixel);
char rgb_to_ascii(int R, int G, int B);

// Block-style grayscale ASCII
const char *grayscale_to_block(unsigned char pixel, Style style = Style::Blocky);

// ANSI color conversions
int rgb_to_ansi256(int R, int G, int B);
std::string rgb_to_ansi256_string(int R, int G, int B);

// high-level drawing functions
void draw_in_terminal(cv::Mat img);
void draw_in_new_file(cv::Mat img, const std::string &filename = "art.txt");

inline std::string rgb_to_bg256_string(int R, int G, int B);
inline void draw_in_terminal_vivid(const cv::Mat &img);

inline std::string rgb_to_bg256_string(int R, int G, int B)
{
    int index = rgb_to_ansi256(R, G, B);
    return "\x1b[48;5;" + std::to_string(index) + "m ";
}

inline void draw_in_terminal_vivid(const cv::Mat &img)
{
    if (img.empty())
    {
        std::cerr << "Image is empty!\n";
        return;
    }

    if (img.channels() != 3)
    {
        std::cerr << "Vivid mode requires a 3-channel (RGB/BGR) image!\n";
        return;
    }

    std::string art;
    art.reserve(img.rows * img.cols * 12); // ANSI heavy

    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            cv::Vec3b p = img.at<cv::Vec3b>(y, x);
            int B = p[0], G = p[1], R = p[2];

            art += rgb_to_bg256_string(R, G, B);
        }
        art += "\x1b[0m\n";
    }

    std::cout << art;
}
