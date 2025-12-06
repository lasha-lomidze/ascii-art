#include "ascii_modes.h"
#include "globals.h"
#include "image_utils.h"
#include <iostream>
#include <fstream>

char grayscale_to_ascii(unsigned char pixel)
{
    const char *ascii = "@%#*+=-:. ";
    int index = pixel * 9 / 255;
    return ascii[index];
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

void draw_in_terminal(cv::Mat img)
{
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            uchar pixel = img.at<uchar>(y, x);
            // std::cout << grayscale_to_ascii(pixel);
            std::cout << grayscale_to_block(pixel);
        }
        std::cout << std::endl;
    }
}
