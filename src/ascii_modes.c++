#include "ascii_modes.h"
#include "globals.h"
#include "image_utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

const std::string ANSI_RESET = "\x1b[0m";

char grayscale_to_ascii(unsigned char pixel)
{
    const char *ascii = "@%#*+=-:. ";
    int index = pixel * 9 / 255;
    return ascii[index];
}

char rgb_to_ascii(int R, int G, int B)
{
    int value = std::max({R, G, B});
    const char *ascii = "@%#*+=-:. ";
    int index = value * 9 / 255;
    return ascii[index];
}

std::string rgb_to_colored_ascii(int R, int G, int B)
{
    return rgb_to_ansi256_string(R, G, B) + rgb_to_ascii(R, G, B) + ANSI_RESET;
}

const char *grayscale_to_block(unsigned char pixel, Style style)
{
    static const char *BLOCKY[] = {"█", "▓", "▒", "░"};
    static const char *EDGY[] = {"█", "▇", "▆", "▅", "▄", "▃", "▂", "▁"};
    static const char *SHARP[] = {"█", "▉", "▊", "▋", "▌", "▍", "▎", "▏", "░"};

    const char **ref;
    int n;

    switch (style)
    {
    case Style::Blocky:
        ref = BLOCKY;
        n = 4;
        break;
    case Style::Edgy:
        ref = EDGY;
        n = 8;
        break;
    case Style::Sharp:
        ref = SHARP;
        n = 9;
        break;
    }

    int index = pixel * (n - 1) / 255;
    return ref[index];
}

int rgb_to_ansi256(int R, int G, int B)
{
    if (std::abs(R - G) < 10 && std::abs(G - B) < 10)
    {
        int gray_index = static_cast<int>(std::round(((R + G + B) / 3.0) - 8) / 10);
        return 232 + std::clamp(gray_index, 0, 23);
    }

    // Map to the 6x6x6 color cube (indices 16-231)
    int r_scaled = static_cast<int>(std::round(R / 255.0 * 5));
    int g_scaled = static_cast<int>(std::round(G / 255.0 * 5));
    int b_scaled = static_cast<int>(std::round(B / 255.0 * 5));

    r_scaled = std::clamp(r_scaled, 0, 5);
    g_scaled = std::clamp(g_scaled, 0, 5);
    b_scaled = std::clamp(b_scaled, 0, 5);

    int ansi_index = 16 + (r_scaled * 36) + (g_scaled * 6) + b_scaled;

    return ansi_index;
}

std::string rgb_to_ansi256_string(int R, int G, int B)
{
    int index = rgb_to_ansi256(R, G, B);
    return "\x1b[38;5;" + std::to_string(index) + "m";
}

void draw_in_new_file(cv::Mat img, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Failed to open file\n";
        return;
    }

    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            uchar pixel = img.at<uchar>(y, x);
            // outFile << grayscale_to_ascii(pixel);
            outFile << grayscale_to_block(pixel);
        }
        outFile << std::endl;
    }

    outFile.close();
}

// take in mode as second argument, style(maybe) as third, add colored: boolean,
void draw_in_terminal(cv::Mat img)
{
    bool is_grayscale = img.channels() == 1;

    if (is_grayscale)
    {
        for (int y = 0; y < img.rows; y++)
        {
            for (int x = 0; x < img.cols; x++)
            {
                uchar pixel = img.at<uchar>(y, x);
                std::cout << grayscale_to_ascii(pixel);
                // std::cout << grayscale_to_block(pixel);
            }
            std::cout << std::endl;
        }
        return;
    }

    if (img.empty() || img.channels() != 3)
    {
        std::cerr << "Image is empty or not a colored image!" << std::endl;
        return;
    }

    for (int y = 0; y < img.rows; ++y)
    {
        for (int x = 0; x < img.cols; ++x)
        {
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);

            unsigned char blue = pixel[0];
            unsigned char green = pixel[1];
            unsigned char red = pixel[2];

            std::cout << rgb_to_colored_ascii(red, green, blue);
        }
        std::cout << std::endl;
    }
}
